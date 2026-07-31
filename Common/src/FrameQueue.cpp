#include "pch.h"
#include <optier/FrameQueue.h>

#include <utility>

namespace optier
{

    FrameQueue::FrameQueue(std::size_t capacity)
        : m_capacity(capacity)
    {
    }

    bool FrameQueue::Push(VideoFrame&& frame)
    {
        std::scoped_lock lock(m_mutex);

        if (m_queue.size() >= m_capacity)
        {
            return false;
        }

        m_queue.push_back(std::move(frame));

        m_condition.notify_one();

        return true;
    }

    bool FrameQueue::TryPush(VideoFrame&& frame)
    {
        return Push(std::move(frame));
    }

    bool FrameQueue::Pop(VideoFrame& frame)
    {
        std::scoped_lock lock(m_mutex);

        if (m_queue.empty())
        {
            return false;
        }

        frame = std::move(m_queue.front());

        m_queue.pop_front();

        return true;
    }

    bool FrameQueue::WaitAndPop(VideoFrame& frame)
    {
        std::unique_lock lock(m_mutex);

        m_condition.wait(lock,
            [this]()
            {
                return !m_queue.empty();
            });

        frame = std::move(m_queue.front());

        m_queue.pop_front();

        return true;
    }

    void FrameQueue::Clear()
    {
        std::scoped_lock lock(m_mutex);

        m_queue.clear();
    }

    bool FrameQueue::Empty() const
    {
        std::scoped_lock lock(m_mutex);

        return m_queue.empty();
    }

    bool FrameQueue::Full() const
    {
        std::scoped_lock lock(m_mutex);

        return m_queue.size() >= m_capacity;
    }

    std::size_t FrameQueue::Size() const
    {
        std::scoped_lock lock(m_mutex);

        return m_queue.size();
    }

    std::size_t FrameQueue::Capacity() const
    {
        return m_capacity;
    }

}