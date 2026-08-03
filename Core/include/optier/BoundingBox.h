#pragma once

#include <cstdint>
#include <string>

#include <opencv2/core/types.hpp>

namespace optier
{

    struct BoundingBox
    {
        //
        // Position
        //
        int X = 0;

        int Y = 0;

        int Width = 0;

        int Height = 0;

        //
        // Detection
        //
        std::string Label;

        float Confidence = 0.0f;

        //
        // Rendering
        //
        cv::Scalar Color =
            cv::Scalar(0, 255, 0);
    };

} // namespace optier