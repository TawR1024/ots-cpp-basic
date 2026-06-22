#pragma once

#include <functional>
#include <future>
#include <queue>
#include <thread>
#include <vector>

namespace astra {

class ThreadPool {
public:
    explicit ThreadPool(size_t num_threads = std::thread::hardware_concurrency());
    ~ThreadPool();

    template <typename F>
    auto submit(F&& task) -> std::future<decltype(task())>;

private:
    void worker_loop();

    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;
    std::mutex mutex_;
    std::condition_variable cv_;
    bool stop_ = false;
};

inline ThreadPool::ThreadPool(size_t num_threads) {
    for (size_t i = 0; i < num_threads; ++i) {
        workers_.emplace_back(&ThreadPool::worker_loop, this);
    }
}

inline ThreadPool::~ThreadPool() {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        stop_ = true;
    }
    cv_.notify_all();
    for (auto& w : workers_) {
        if (w.joinable()) w.join();
    }
}

inline void ThreadPool::worker_loop() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(mutex_);
            cv_.wait(lock, [this] { return stop_ || !tasks_.empty(); });
            if (stop_ && tasks_.empty()) return;
            task = std::move(tasks_.front());
            tasks_.pop();
        }
        task();
    }
}

template <typename F>
auto ThreadPool::submit(F&& task) -> std::future<decltype(task())> {
    using ReturnType = decltype(task());
    auto packaged = std::make_shared<std::packaged_task<ReturnType()>>(std::forward<F>(task));
    auto future = packaged->get_future();
    {
        std::lock_guard<std::mutex> lock(mutex_);
        tasks_.emplace([packaged]() { (*packaged)(); });
    }
    cv_.notify_one();
    return future;
}

} // namespace astra
