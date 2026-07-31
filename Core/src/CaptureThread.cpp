#include "pch.h"
#include <optier/CaptureThread.h>

#include <utility>

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

            m_queue.Push(std::move(frame));
        }
    }

}