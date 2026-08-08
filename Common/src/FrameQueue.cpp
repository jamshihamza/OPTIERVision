#include "pch.h"
#include <optier/FrameQueue.h>

#include <utility>
#include <iostream>

namespace optier
{

    FrameQueue::FrameQueue(std::size_t capacity)
        : m_capacity(capacity)
    {
    }

    bool FrameQueue::Push(VideoFrame&& frame)
    {
        //
// Statistics
//
        ++m_pushCount;

        if (m_queue.size() > m_peakSize)
        {
            m_peakSize = m_queue.size();
        }

        std::scoped_lock lock(m_mutex);

        if (m_shutdown)
        {
            return false;
        }
        if (m_queue.size() >= m_capacity)
        {
            ++m_droppedFrames;
			++m_dropCount;
            return false;
        }

        m_queue.push_back(std::move(frame));

		++m_totalPushes;

        if (m_queue.size() > m_peakQueueSize)
        {
            m_peakQueueSize = m_queue.size();
        }

        m_condition.notify_one();

        //
// Report every 60 successful pushes
//
        if ((m_pushCount % 60) == 0)
        {
            std::cout << "\n";
            std::cout << "========================================\n";
            std::cout << " Queue Statistics\n";
            std::cout << "========================================\n";

            std::cout
                << "Current Queue Size : "
                << m_queue.size()
                << "\n";

            std::cout
                << "Peak Queue Size    : "
                << m_peakSize
                << "\n";

            std::cout
                << "Total Pushes       : "
                << m_pushCount
                << "\n";

            std::cout
                << "Total Pops         : "
                << m_popCount
                << "\n";

            std::cout
                << "Dropped Frames     : "
                << m_dropCount
                << "\n";

            std::cout << "========================================\n\n";
        }

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

		++m_totalPops;

        return true;
    }

    bool FrameQueue::WaitAndPop(VideoFrame& frame)
    {
        std::unique_lock lock(m_mutex);

        m_condition.wait(lock,
            [this]()
            {
                return !m_queue.empty() || m_shutdown;
            });

        if (m_shutdown && m_queue.empty())
        {
            return false;
        }

        frame = std::move(m_queue.front());

        m_queue.pop_front();

		++m_totalPops;
		++m_popCount;

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

    void FrameQueue::Shutdown()
    {
        {
            std::scoped_lock lock(m_mutex);

            m_shutdown = true;
        }

        m_condition.notify_all();
    }
    void FrameQueue::Reset()
    {
        std::scoped_lock lock(m_mutex);

        m_shutdown = false;
    }
    bool FrameQueue::IsShutdown() const
    {
        std::scoped_lock lock(m_mutex);

        return m_shutdown;
    }

    std::uint64_t FrameQueue::TotalPushes() const
    {
        std::scoped_lock lock(m_mutex);
        return m_totalPushes;
    }

    std::uint64_t FrameQueue::TotalPops() const
    {
        std::scoped_lock lock(m_mutex);
        return m_totalPops;
    }

    std::uint64_t FrameQueue::DroppedFrames() const
    {
        std::scoped_lock lock(m_mutex);
        return m_droppedFrames;
    }

    std::size_t FrameQueue::PeakQueueSize() const
    {
        std::scoped_lock lock(m_mutex);
        return m_peakQueueSize;
    }
}