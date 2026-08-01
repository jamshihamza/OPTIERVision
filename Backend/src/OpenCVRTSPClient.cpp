#include "pch.h"

#include <optier/OpenCVRTSPClient.h>
#include <optier/VideoFrame.h>

#include <opencv2/core/mat.hpp>
#include <opencv2/videoio.hpp>

#include <memory>
#include <chrono>

namespace optier
{

    class OpenCVRTSPClient::Impl
    {
    public:

        cv::VideoCapture Capture;

        cv::Mat Frame;

        StreamState State = StreamState::Disconnected;

        std::uint64_t FrameNumber = 0;
    };

    OpenCVRTSPClient::OpenCVRTSPClient()
        : m_impl(std::make_unique<Impl>())
    {
    }

    OpenCVRTSPClient::~OpenCVRTSPClient()
    {
        Disconnect();
    }

    bool OpenCVRTSPClient::Connect(const std::string& url)
    {
        if (url.empty())
        {
            m_impl->State = StreamState::Error;
            return false;
        }

        if (IsConnected())
        {
            Disconnect();
        }

        m_impl->State = StreamState::Connecting;

        if (!m_impl->Capture.open(url, cv::CAP_FFMPEG))
        {
            m_impl->State = StreamState::Error;
            return false;
        }

        m_impl->FrameNumber = 0;
        m_impl->State = StreamState::Streaming;

        return true;
    }

    void OpenCVRTSPClient::Disconnect()
    {
        if (m_impl->Capture.isOpened())
        {
            m_impl->Capture.release();
        }

        m_impl->Frame.release();

        m_impl->FrameNumber = 0;

        m_impl->State = StreamState::Disconnected;
    }

    bool OpenCVRTSPClient::IsConnected() const
    {
        return
            m_impl->Capture.isOpened() &&
            m_impl->State == StreamState::Streaming;
    }

    bool OpenCVRTSPClient::ReadFrame(VideoFrame& frame)
    {
        if (!IsConnected())
        {
            return false;
        }

        if (!m_impl->Capture.read(m_impl->Frame))
        {
            m_impl->State = StreamState::Error;
            return false;
        }

        if (m_impl->Frame.empty())
        {
            m_impl->State = StreamState::Error;
            return false;
        }

        ++m_impl->FrameNumber;

        frame.Width =
            static_cast<std::uint32_t>(m_impl->Frame.cols);

        frame.Height =
            static_cast<std::uint32_t>(m_impl->Frame.rows);

        frame.FrameNumber =
            m_impl->FrameNumber;

        frame.Timestamp =
            std::chrono::steady_clock::now();

        frame.Image =
            std::make_shared<cv::Mat>(
                m_impl->Frame.clone());

        return true;
    }

}