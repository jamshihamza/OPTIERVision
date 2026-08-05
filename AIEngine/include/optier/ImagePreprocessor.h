#pragma once

#include <vector>

#include <opencv2/core/mat.hpp>

namespace optier
{

    class ImagePreprocessor
    {
    public:

        ImagePreprocessor() = default;

        bool Preprocess(
            const cv::Mat& inputImage,
            std::vector<float>& outputTensor);

    private:

        cv::Mat LetterboxResize(
            const cv::Mat& image,
            int targetWidth = 640,
            int targetHeight = 640);

        cv::Mat ConvertToRGB(
            const cv::Mat& image);

        cv::Mat ConvertToFloat(
            const cv::Mat& image);

        void ConvertToTensor(
            const cv::Mat& image,
            std::vector<float>& tensor);
    };

} // namespace optier