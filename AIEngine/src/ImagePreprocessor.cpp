#include "pch.h"

#include <optier/ImagePreprocessor.h>

#include <opencv2/imgproc.hpp>

namespace optier
{

    bool ImagePreprocessor::Preprocess(
        const cv::Mat& input,
        cv::Mat& output)
    {
        //
        // Validate input image.
        //
        if (input.empty())
        {
            return false;
        }

        //
        // Resize image to YOLO input resolution.
        //
        cv::resize(
            input,
            output,
            cv::Size(
                TargetWidth,
                TargetHeight));

        //
        // TODO:
        //
        // 1. Letterbox while preserving aspect ratio.
        // 2. Convert BGR → RGB.
        // 3. Convert uint8 → float32.
        // 4. Normalize to [0.0, 1.0].
        // 5. Convert NHWC → NCHW tensor.
        //

        return true;
    }

} // namespace optier