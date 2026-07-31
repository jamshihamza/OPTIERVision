#pragma once

#include <memory>
#include <string>

#include <optier/IRTSPClient.h>
#include <optier/StreamState.h>

namespace cv
{
    class VideoCapture;
}

namespace optier
{

    class OpenCVRTSPClient final : public IRTSPClient
    {
    public:

        OpenCVRTSPClient();

        ~OpenCVRTSPClient() override;

    public:

        bool Connect(
            const std::string& url) override;

        void Disconnect() override;

        bool IsConnected() const override;

        bool ReadFrame(
            VideoFrame& frame) override;

    private:

        std::unique_ptr<cv::VideoCapture> m_capture;

        StreamState m_state = StreamState::Disconnected;

        std::uint64_t m_frameNumber = 0;
    };

}