#include "pch.h"

#include <optier/ConsumerThread.h>

#include <chrono>
#include <thread>
#include <iostream>

namespace optier
{

    ConsumerThread::ConsumerThread(
        FrameQueue& queue,
        FrameProcessorPipeline& pipeline)
        : m_queue(queue)
        , m_pipeline(pipeline)
    {
    }

    ConsumerThread::~ConsumerThread()
    {
        Stop();
    }

    bool ConsumerThread::Start()
    {
        if (m_running.load())
        {
            return false;
        }

        m_running.store(true);

        m_thread =
            std::thread(
                &ConsumerThread::Run,
                this);

        return true;
    }

    void ConsumerThread::Stop()
    {
        if (!m_running.load())
        {
            return;
        }

        m_running.store(false);

        m_queue.Shutdown();

        if (m_thread.joinable())
        {
            m_thread.join();
        }
    }

    bool ConsumerThread::IsRunning() const
    {
        return m_running.load();
    }

    std::uint64_t ConsumerThread::ProcessedFrames() const
    {
        return m_processedFrames.load();
    }

    void ConsumerThread::Run()
    {
        while (m_running.load())
        {
            VideoFrame frame;

            //
            // Wait for next frame
            //
            if (!m_queue.WaitAndPop(frame))
            {
                break;
            }

            
            //
            // Execute the frame processing pipeline
            //
            bool ok =
                m_pipeline.ProcessFrame(frame);

           

            //
            // Skip failed frames
            //
            if (!ok)
            {
                continue;
            }

          
            //
            // Statistics
            //
            ++m_processedFrames;

            if ((m_processedFrames.load() % 60) == 0)
            {
                std::cout << "\n";
                std::cout << "========================================\n";
                std::cout << " Queue Statistics\n";
                std::cout << "========================================\n";

                std::cout
                    << "Current Queue Size : "
                    << m_queue.Size()
                    << "\n";

                std::cout
                    << "Peak Queue Size    : "
                    << m_queue.PeakQueueSize()
                    << "\n";

                std::cout
                    << "Total Pushes       : "
                    << m_queue.TotalPushes()
                    << "\n";

                std::cout
                    << "Total Pops         : "
                    << m_queue.TotalPops()
                    << "\n";

                std::cout
                    << "Dropped Frames     : "
                    << m_queue.DroppedFrames()
                    << "\n";

                std::cout
                    << "========================================\n\n";
            }
        }
    }

} // namespace optier