#include "pch.h"
#include <optier/ConsumerThread.h>

namespace optier
{

    ConsumerThread::ConsumerThread(FrameQueue& queue)
        : m_queue(queue)
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

        m_thread = std::thread(&ConsumerThread::Run, this);

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

            if (!m_queue.WaitAndPop(frame))
            {
                break;
            }

            //
            // Future:
            // Renderer
            // AI Engine
            // Recorder
            //

            ++m_processedFrames;
        }
    }

} // namespace optier