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
    return false;
}

void OpenCVRTSPClient::Disconnect()
{
}

bool OpenCVRTSPClient::IsConnected() const
{
    return false;
}

bool OpenCVRTSPClient::ReadFrame(
    VideoFrame& frame)
{
    return false;
}
}