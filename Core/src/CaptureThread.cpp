#include "pch.h"
#include <optier/CaptureThread.h>
#include <chrono>
#include <utility>
#include <iostream>

namespace optier
{

    CaptureThread::CaptureThread(OpenCVRTSPClient& client,
        FrameQueue& queue)
        : m_client(client)
        , m_queue(queue)
    {
    }

    CaptureThread::~CaptureThread()
    {
        Stop();
    }

    bool CaptureThread::Start()
    {
        if (m_running.load())
        {
            return false;
        }

        m_running.store(true);

        m_thread = std::thread(&CaptureThread::Run, this);

        return true;
    }

    void CaptureThread::Stop()
    {
        if (!m_running.load())
        {
            return;
        }

        m_running.store(false);

        if (m_thread.joinable())
        {
            m_thread.join();
        }
    }

    bool CaptureThread::IsRunning() const
    {
        return m_running.load();
    }

    void CaptureThread::Run()
    {
        while (m_running.load())
        {
            VideoFrame frame;

            if (!m_client.ReadFrame(frame))
            {
                continue;
            }

            //
			//Statistics
            //
			++m_capturedFrames;

            if ((m_capturedFrames % 30) == 0)
            {
                const auto now =
                    std::chrono::steady_clock::now();

                const auto elapsed =
                    std::chrono::duration_cast<
                    std::chrono::milliseconds>(
                        now - m_lastReport);

                if (elapsed.count() > 0)
                {
                    const double fps =
                        static_cast<double>(m_capturedFrames) /
                        (elapsed.count() / 1000.0);

                    std::cout << "\n";
                    std::cout << "========================================\n";
                    std::cout << " Capture Statistics\n";
                    std::cout << "========================================\n";
                    std::cout << "Captured Frames : "
                        << m_capturedFrames
                        << "\n";

                    std::cout << "Capture FPS     : "
                        << fps
                        << "\n";

                    std::cout << "========================================\n\n";

                    m_capturedFrames = 0;
                    m_lastReport = now;
                }
            }

            m_queue.Push(std::move(frame));
        }
    }

}