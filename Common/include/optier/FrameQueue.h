#pragma once

#include <condition_variable>
#include <cstddef>
#include <deque>
#include <mutex>

#include <optier/VideoFrame.h>

namespace optier
{

    class FrameQueue
    {
    public:

        explicit FrameQueue(std::size_t capacity);

        ~FrameQueue() = default;

        FrameQueue(const FrameQueue&) = delete;
        FrameQueue& operator=(const FrameQueue&) = delete;

        FrameQueue(FrameQueue&&) = delete;
        FrameQueue& operator=(FrameQueue&&) = delete;

    public:

        bool Push(VideoFrame&& frame);

        bool TryPush(VideoFrame&& frame);

        bool Pop(VideoFrame& frame);

        bool WaitAndPop(VideoFrame& frame);

        void Clear();

        bool Empty() const;

        bool Full() const;

        std::size_t Size() const;

        std::size_t Capacity() const;

        void Shutdown();

        void Reset();

        bool IsShutdown() const;

    private:

        mutable std::mutex m_mutex;

        std::condition_variable m_condition;

        std::deque<VideoFrame> m_queue;

        std::size_t m_capacity;

        bool m_shutdown{ false };
    };

}