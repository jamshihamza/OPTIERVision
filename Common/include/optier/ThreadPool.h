#pragma once

#include <condition_variable>
#include <cstddef>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace optier
{

    class ThreadPool
    {
    public:

        explicit ThreadPool(
            std::size_t threadCount);

        ~ThreadPool();

        ThreadPool(const ThreadPool&) = delete;
        ThreadPool& operator=(const ThreadPool&) = delete;

        void Enqueue(
            std::function<void()> task);

        void Shutdown();

    private:

        void Worker();

    private:

        std::vector<std::thread> m_threads;

        std::queue<std::function<void()>> m_tasks;

        std::mutex m_mutex;

        std::condition_variable m_condition;

        bool m_stop;
    };

}