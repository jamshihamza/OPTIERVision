#include "pch.h"

#include <optier/ThreadPool.h>

namespace optier
{

    ThreadPool::ThreadPool(std::size_t threadCount)
        : m_stop(false)
    {
        for (std::size_t i = 0; i < threadCount; ++i)
        {
            m_threads.emplace_back(&ThreadPool::Worker, this);
        }
    }

    ThreadPool::~ThreadPool()
    {
        Shutdown();
    }

    void ThreadPool::Enqueue(std::function<void()> task)
    {
        {
            std::lock_guard<std::mutex> lock(m_mutex);

            if (m_stop)
            {
                return;
            }

            m_tasks.push(std::move(task));
        }

        m_condition.notify_one();
    }

    void ThreadPool::Shutdown()
    {
        {
            std::lock_guard<std::mutex> lock(m_mutex);

            if (m_stop)
            {
                return;
            }

            m_stop = true;
        }

        m_condition.notify_all();

        for (std::thread& thread : m_threads)
        {
            if (thread.joinable())
            {
                thread.join();
            }
        }

        m_threads.clear();
    }

    void ThreadPool::Worker()
    {
        while (true)
        {
            std::function<void()> task;

            {
                std::unique_lock<std::mutex> lock(m_mutex);

                m_condition.wait(lock,
                    [this]
                    {
                        return m_stop || !m_tasks.empty();
                    });

                if (m_stop && m_tasks.empty())
                {
                    return;
                }

                task = std::move(m_tasks.front());
                m_tasks.pop();
            }

            task();
        }
    }

}