#pragma once

#include <atomic>
#include <cstdint>
#include <thread>

#include <optier/FrameQueue.h>
#include <optier/FrameProcessorPipeline.h>

namespace optier
{

    class ConsumerThread
    {
    public:

        ConsumerThread(
            FrameQueue& queue,
            FrameProcessorPipeline& pipeline);

        ~ConsumerThread();

        ConsumerThread(const ConsumerThread&) = delete;
        ConsumerThread& operator=(const ConsumerThread&) = delete;

        ConsumerThread(ConsumerThread&&) = delete;
        ConsumerThread& operator=(ConsumerThread&&) = delete;

    public:

        bool Start();

        void Stop();

        bool IsRunning() const;

        std::uint64_t ProcessedFrames() const;

    private:

        void Run();

    private:

        FrameQueue& m_queue;

        FrameProcessorPipeline& m_pipeline;

        std::thread m_thread;

        std::atomic<bool> m_running{ false };

        std::atomic<std::uint64_t> m_processedFrames{ 0 };
    };

} // namespace optier