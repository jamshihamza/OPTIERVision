#include "pch.h"

#include <optier/OpenCVRTSPClient.h>

#include <opencv2/videoio.hpp>

namespace optier
{

    OpenCVRTSPClient::OpenCVRTSPClient()
        : m_capture(std::make_unique<cv::VideoCapture>())
    {
    }

    OpenCVRTSPClient::~OpenCVRTSPClient()
    {
        Disconnect();
    }
    bool OpenCVRTSPClient::Connect(
        const std::string& url)
    {
        if (url.empty())
        {
            m_state = StreamState::Error;
            return false;
        }

        if (IsConnected())
        {
            Disconnect();
        }

        m_state = StreamState::Connecting;

        if (!m_capture->open(url))
        {
            m_state = StreamState::Error;
            return false;
        }

        m_state = StreamState::Streaming;

        return true;
    }

    void OpenCVRTSPClient::Disconnect()
    {
        if (m_capture && m_capture->isOpened())
        {
            m_capture->release();
        }

        m_frameNumber = 0;

        m_state = StreamState::Disconnected;
    }

    bool OpenCVRTSPClient::IsConnected() const
    {
        return m_capture &&
            m_capture->isOpened() &&
            m_state == StreamState::Streaming;
    }

bool OpenCVRTSPClient::ReadFrame(
    VideoFrame& frame)
{
    return false;
}
}