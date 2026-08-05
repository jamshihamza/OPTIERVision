#pragma once

#include <opencv2/core/mat.hpp>

namespace optier
{

    class ImagePreprocessor
    {
    public:

        ImagePreprocessor() = default;

        ~ImagePreprocessor() = default;

        bool Preprocess(
            const cv::Mat& input,
            cv::Mat& output);

    private:

        static constexpr int TargetWidth = 640;

        static constexpr int TargetHeight = 640;
    };

} // namespace optier