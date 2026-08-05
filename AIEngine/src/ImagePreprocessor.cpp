#include "pch.h"

#include <optier/ImagePreprocessor.h>

#include <opencv2/imgproc.hpp>

namespace optier
{

    bool ImagePreprocessor::Preprocess(
        const cv::Mat& inputImage,
        std::vector<float>& outputTensor)
    {
        if (inputImage.empty())
        {
            return false;
        }

        cv::Mat resized =
            LetterboxResize(inputImage);

        cv::Mat rgb =
            ConvertToRGB(resized);

        cv::Mat normalized =
            ConvertToFloat(rgb);

        ConvertToTensor(
            normalized,
            outputTensor);

        return true;
    }

    cv::Mat ImagePreprocessor::LetterboxResize(
        const cv::Mat& image,
        int targetWidth,
        int targetHeight)
    {
        const float scale =
            std::min(
                static_cast<float>(targetWidth) /
                image.cols,
                static_cast<float>(targetHeight) /
                image.rows);

        const int resizedWidth =
            static_cast<int>(image.cols * scale);

        const int resizedHeight =
            static_cast<int>(image.rows * scale);

        cv::Mat resized;

        cv::resize(
            image,
            resized,
            cv::Size(
                resizedWidth,
                resizedHeight));

        cv::Mat output(
            targetHeight,
            targetWidth,
            image.type(),
            cv::Scalar(
                114,
                114,
                114));

        const int offsetX =
            (targetWidth - resizedWidth) / 2;

        const int offsetY =
            (targetHeight - resizedHeight) / 2;

        resized.copyTo(
            output(
                cv::Rect(
                    offsetX,
                    offsetY,
                    resizedWidth,
                    resizedHeight)));

        return output;
    }

    cv::Mat ImagePreprocessor::ConvertToRGB(
        const cv::Mat& image)
    {
        cv::Mat rgb;

        cv::cvtColor(
            image,
            rgb,
            cv::COLOR_BGR2RGB);

        return rgb;
    }

    cv::Mat ImagePreprocessor::ConvertToFloat(
        const cv::Mat& image)
    {
        cv::Mat output;

        image.convertTo(
            output,
            CV_32FC3,
            1.0 / 255.0);

        return output;
    }

    void ImagePreprocessor::ConvertToTensor(
        const cv::Mat& image,
        std::vector<float>& tensor)
    {
        constexpr int channels = 3;
        constexpr int height = 640;
        constexpr int width = 640;

        tensor.resize(
            channels * height * width);

        std::vector<cv::Mat> splitChannels;

        cv::split(
            image,
            splitChannels);

        for (int c = 0; c < channels; ++c)
        {
            std::memcpy(
                tensor.data() + c * height * width,
                splitChannels[c].data,
                height * width * sizeof(float));
        }
    }

} // namespace optier