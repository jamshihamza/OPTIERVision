#pragma once

#include <atomic>
#include <thread>

#include <optier/FrameQueue.h>
#include <optier/OpenCVRTSPClient.h>

namespace optier
{

    class CaptureThread
    {
    public:

        CaptureThread(OpenCVRTSPClient& client,
            FrameQueue& queue);

        ~CaptureThread();

        CaptureThread(const CaptureThread&) = delete;
        CaptureThread& operator=(const CaptureThread&) = delete;

        CaptureThread(CaptureThread&&) = delete;
        CaptureThread& operator=(CaptureThread&&) = delete;

    public:

        bool Start();

        void Stop();

        bool IsRunning() const;

    private:

        void Run();

    private:

        OpenCVRTSPClient& m_client;

        FrameQueue& m_queue;

        std::thread m_thread;

        std::atomic<bool> m_running{ false };
    };

}