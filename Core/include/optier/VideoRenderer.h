#pragma once

#include <mutex>
#include <string>

#include <opencv2/core/mat.hpp>

#include <optier/IFrameProcessor.h>

namespace optier
{

    class VideoRenderer final : public IFrameProcessor
    {
    public:

        explicit VideoRenderer(
            std::string windowName = "OPTIER Vision");

        ~VideoRenderer() override;

    public:

        bool ProcessFrame(
            VideoFrame& frame) override;

        void Display();

    private:

        std::string m_windowName;

        std::mutex m_mutex;

        cv::Mat m_latestFrame;
    };

}