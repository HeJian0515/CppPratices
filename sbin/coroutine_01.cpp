#include <coroutine>
#include <iostream>

template <typename T>
struct coro_ret {
	struct promise_type;
	using handle_type = std::coroutine_handle<promise_type>;
	// 协程句柄
	handle_type coro_handle_;

	struct promise_type {
		promise_type() {
			std::cout << "promise constructor invoked." << std::endl;
		}

		~promise_type() = default;

		// 生成协程返回值
		auto get_return_object() {
			std::cout << "get_return_object invoked" << std::endl;
			return coro_ret<T>{handle_type::from_promise(*this)};
		}

		auto initial_suspend() {
			std::cout << "initial_suspend invoked." << std::endl;
			return std::suspend_always{};
		}

		void return_void() {
			std::cout << "return void invoked." << std::endl;
		}

		auto yield_value(const T& v) {
			std::cout << "yield_value invoked." << std::endl;
			return_data_ = v;
			return std::suspend_always{};
		}

		auto final_suspend() noexcept {
			std::cout << "finial_suspend invoked." << std::endl;
			return std::suspend_always{};
		}

		void unhandled_exception() {
			std::cout << "unhandled_exception invoked." << std::endl;
			std::exit(1);
		}

		T return_data_;
	};


	coro_ret(handle_type h) : coro_handle_(h) {}

	~coro_ret() {
		if (coro_handle_) {
			coro_handle_.destroy();
		}
	}

	bool resume() {
		if (!coro_handle_.done()) {
			coro_handle_.resume();
		}
		return coro_handle_.done();
	}

	bool done() const {
		return coro_handle_.done();
	}

	T get() {
		return coro_handle_.promise().return_data_;
	}
};


coro_ret<int> number_generator(int begin, int count) {
	std::cout << "number_generator invoked." << std::endl;
	for (int i = begin; i < count; ++i) {
		co_yield i;
	}
	co_return;
}

int main(int argc, char* argv[])
{
	auto g = number_generator(1, 10);
	std::cout << "begin to run!" << std::endl;
	while (!g.resume()) {
		std::cout << "get number:" << g.get() << std::endl;
	}
	std::cout << "coroutine done, return value:" << g.get() << std::endl;
	return 0;
}