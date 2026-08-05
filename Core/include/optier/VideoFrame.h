#pragma once

#include <chrono>
#include <cstdint>
#include <memory>
#include <vector>

#include <opencv2/core/mat.hpp>

#include <optier/BoundingBox.h>
#include <optier/DetectionCollection.h>
#include <optier/FrameStatistics.h>
#include <optier/PreprocessMetadata.h>

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
        // Image preprocessing metadata.
        //
        PreprocessMetadata Preprocess;
        //
        // Runtime Statistics
        //
        FrameStatistics Statistics;

        //
        // AI Detection Results
        //
        DetectionCollection Detections;

        //
        // Rendering Data
        //
        std::vector<BoundingBox> BoundingBoxes;
    };

} // namespace optier