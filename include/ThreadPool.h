#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

class ThreadPool
{
private:
   std::vector<std::thread> workers_;

   std::queue<std::function<void()>> tasks_; // 任务队列

   std::mutex queue_mutex_;
   std::condition_variable condition_;
   bool stop_; 

public:
    ThreadPool(std::size_t threads);
    ~ThreadPool();

public:
    template<typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<decltype(f(args...))>;
};


// 启动相应数量的工作线程
ThreadPool::ThreadPool(std::size_t threads) : stop_(false)
{   
    workers_.reserve(threads);
    for (std::size_t i = 0; i < threads; ++i)
    {
        workers_.emplace_back(
            [this]() {
                for (;;)
                {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock{this->queue_mutex_};
                        this->condition_.wait(lock, [this]{return this->stop_ || !this->tasks_.empty();});

                        if (this->stop_ && this->tasks_.empty()) return;

                        task = std::move(this->tasks_.front());
                        this->tasks_.pop();
                    }
                    task();
                }
            }
        );
    }
}


ThreadPool::~ThreadPool() 
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        stop_ = true;
    }

    condition_.notify_all();
    for (auto& woker : workers_) {
        woker.join();
    }
}

template<typename F, typename... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args) -> std::future<decltype(f(args...))>
{
    using return_type = decltype(f(args...));

    auto task = std::make_shared<std::packaged_task<return_type ()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );

    std::future<return_type> res = task->get_future();

    {
        std::unique_lock<std::mutex> lock{queue_mutex_};

        if (stop_) throw std::runtime_error{"enqueue on stopped ThreadPool"};

        tasks_.emplace([task]() { (*task)();});
    }
    condition_.notify_one();
    return res;
}


#endif // __THREADPOOL_H__