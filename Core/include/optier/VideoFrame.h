#pragma once

#include <chrono>
#include <cstdint>
#include <memory>

#include <opencv2/core/mat.hpp>

#include <optier/FrameStatistics.h>

namespace optier
{

    struct VideoFrame
    {
        //
        // Frame Identity
        //
        std::uint32_t Width = 0;

        std::uint32_t Height = 0;

        std::uint64_t FrameNumber = 0;

        std::chrono::steady_clock::time_point Timestamp;

        //
        // Image
        //
        std::shared_ptr<cv::Mat> Image;

        //
        // Runtime Statistics
        //
        FrameStatistics Statistics;
    };

}