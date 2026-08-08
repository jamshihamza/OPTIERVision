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

        OpenCVRTSPClient& m_client;

        FrameQueue& m_queue;

        std::thread m_thread;

        std::atomic<bool> m_running{ false };

        //
        // Performance Statistics
        //
        std::uint64_t m_capturedFrames{ 0 };

        std::chrono::steady_clock::time_point m_lastReport =
            std::chrono::steady_clock::now();
    };

}