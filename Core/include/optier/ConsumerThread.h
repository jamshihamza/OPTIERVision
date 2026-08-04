#pragma once

#include <atomic>
#include <cstdint>
#include <thread>

#include <optier/FrameQueue.h>
#include <optier/FrameProcessorPipeline.h>
#include <optier/PerformanceMonitorProcessor.h>

namespace optier
{

    class ConsumerThread
    {
    public:

        ConsumerThread(
            FrameQueue& queue,
            FrameProcessorPipeline& pipeline);

        ~ConsumerThread();

        ConsumerThread(
            const ConsumerThread&) = delete;

        ConsumerThread& operator=(
            const ConsumerThread&) = delete;

        bool Start();

        void Stop();

        bool IsRunning() const;

        std::uint64_t ProcessedFrames() const;

    private:

        void Run();

    private:

        //
        // Shared objects
        //
        FrameQueue& m_queue;

        FrameProcessorPipeline& m_pipeline;

       
        //
        // Worker thread
        //
        std::thread m_thread;

        //
        // Thread state
        //
        std::atomic<bool> m_running{ false };

        //
        // Statistics
        //
        std::atomic<std::uint64_t> m_processedFrames{ 0 };
    };

} // namespace optier