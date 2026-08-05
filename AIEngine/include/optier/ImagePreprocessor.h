#pragma once

#include <vector>

#include <opencv2/core/mat.hpp>
#include <optier/VideoFrame.h>
#include <optier/PreprocessMetadata.h>

namespace optier
{

    class ImagePreprocessor
    {
    public:

        ImagePreprocessor() = default;

        bool Preprocess(
            VideoFrame& frame,
            std::vector<float>& outputTensor);

    private:

        cv::Mat LetterboxResize(
            const cv::Mat& image,
            const PreprocessMetadata& preprocess);

        cv::Mat ConvertToRGB(
            const cv::Mat& image);

        cv::Mat ConvertToFloat(
            const cv::Mat& image);

        void ConvertToTensor(
            const cv::Mat& image,
            std::vector<float>& tensor);
    };

} // namespace optier