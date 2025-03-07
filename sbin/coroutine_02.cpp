/*
 auto x = co_await awaitable
 执行awaitable.await_ready()，这个函数通常返回false,
 表示co_await还没有准备好计算一个值给x
 所以协程会暂停并准备交出控制权；

 在交出控制权之前会执行awaitable.await_suspend(handle)，
 这个函数一般会将协程handle保存在某个地方，
 以便后续的恢复或销毁

 移交控制权给调用者或恢复者。从调用者或恢复者的角度来看，就是协程返回了。
 然后，如果在其它地方有人调用了handle.resume()
 那么这个协程就又被恢复了，被恢复的协程立刻执行以下操作：
 1 执行 awaitable.await_resume()
 2 将await_resume()的返回值赋值给x
 由此，auto x = co_await awaitable; 就算执行完毕了。
 */

#include <coroutine>
#include <iostream>
#include <stdexcept>
#include <thread>

auto switch_to_new_thread(std::jthread& out) {
	struct awaitable {
		std::jthread* p_out;

		bool await_ready() { return false; }
		void await_suspend(std::coroutine_handle<> h) {
			std::jthread& out = *p_out;
			if (out.joinable()) {
				throw std::runtime_error("jthread 输出参数非空");
			}
			out = std::jthread([h] { h.resume(); }); // 调用了handle.resume,那么这个协程恢复
			// 潜在的未定义行为：访问其潜在被销毁的 *this
			// std::cout << "新线程 ID: " << p_out->get_id() << '\n';
			std::cout << "新线程 ID：" << out.get_id() << '\n';
		}
		void await_resume() {}
	};

	return awaitable{&out};
}

struct task {
	struct promise_type {
		task get_return_object() { return {}; }
		std::suspend_never initial_suspend() { return {}; }
		std::suspend_never final_suspend() noexcept { return {}; }
		void return_void() {}
		void unhandled_exception() {}
	};
};

task resuming_on_new_thread(std::jthread& out) {
	// task::promise_type promise;
	// task ret = promise.get_return_object();
	// co await promise.initial_suspend();

	std::cout << "协程开始，线程ID: " << std::this_thread::get_id() << '\n';
	co_await switch_to_new_thread(out);
	// 等待器在此销毁
	std::cout << "协程恢复，线程 ID: " << std::this_thread::get_id() << '\n';

	// co_await promise.final_suspend();
}

int main() {
	std::jthread out;
	resuming_on_new_thread(out);
}

/*
协程开始，线程ID: 18632
新线程 ID：1368
协程恢复，线程 ID: 1368
 */

// 当一个协程被调用时，会创建Promise对象，然后编译器会在各个阶段插入一些代码
/*{
	co_await promise initial_suspend();
	try {
		// body statements
	} catch(...) {
		promise.unhandled_exception();
	}

	FinalSuspend:
		co_await promise.final_suspend();
}*/