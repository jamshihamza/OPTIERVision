#pragma once

#include <chrono>
#include <cstdint>
#include <memory>

#include <opencv2/core/mat.hpp>

namespace optier
{

    struct VideoFrame
    {
        std::uint32_t Width = 0;

        std::uint32_t Height = 0;

        std::uint64_t FrameNumber = 0;

        std::chrono::steady_clock::time_point Timestamp;

        std::shared_ptr<cv::Mat> Image;
    };

}