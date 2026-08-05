#include "pch.h"

#include <optier/ImagePreprocessor.h>

#include <opencv2/imgproc.hpp>

namespace optier
{

    bool ImagePreprocessor::Preprocess(
        VideoFrame& frame,
        std::vector<float>& outputTensor)
    {
        //
        // Validate frame.
        //
        if (!frame.Image)
        {
            return false;
        }

        cv::Mat& inputImage =
            *frame.Image;

        if (inputImage.empty())
        {
            return false;
        }

        //
        // Store original image information.
        //
        frame.Preprocess.OriginalWidth =
            inputImage.cols;

        frame.Preprocess.OriginalHeight =
            inputImage.rows;

        //
        // Model input size.
        //
        constexpr int modelWidth = 640;
        constexpr int modelHeight = 640;

        frame.Preprocess.ModelWidth =
            modelWidth;

        frame.Preprocess.ModelHeight =
            modelHeight;

        //
        // Compute resize scale.
        //
        const float scale =
            std::min(
                static_cast<float>(modelWidth) /
                inputImage.cols,
                static_cast<float>(modelHeight) /
                inputImage.rows);

        frame.Preprocess.Scale =
            scale;

        //
        // Compute resized dimensions.
        //
        const int resizedWidth =
            static_cast<int>(
                inputImage.cols * scale);

        const int resizedHeight =
            static_cast<int>(
                inputImage.rows * scale);

        //
        // Compute letterbox padding.
        //
        frame.Preprocess.PadLeft =
            (modelWidth - resizedWidth) / 2;

        frame.Preprocess.PadTop =
            (modelHeight - resizedHeight) / 2;

        frame.Preprocess.PadRight =
            modelWidth -
            resizedWidth -
            frame.Preprocess.PadLeft;

        frame.Preprocess.PadBottom =
            modelHeight -
            resizedHeight -
            frame.Preprocess.PadTop;

        //
        // Existing preprocessing pipeline.
        //
        cv::Mat resized =
            LetterboxResize(
                inputImage,
                frame.Preprocess);

        cv::Mat rgb =
            ConvertToRGB(
                resized);

        cv::Mat normalized =
            ConvertToFloat(
                rgb);

        ConvertToTensor(
            normalized,
            outputTensor);

        return true;
    }

    cv::Mat ImagePreprocessor::LetterboxResize(
        const cv::Mat& image,
        const PreprocessMetadata& preprocess)
    {
        const int targetWidth =
            preprocess.ModelWidth;

        const int targetHeight =
            preprocess.ModelHeight;

        const float scale =
            preprocess.Scale;

        const int resizedWidth =
            static_cast<int>(
                image.cols * scale);

        const int resizedHeight =
            static_cast<int>(
                image.rows * scale);

        const int offsetX =
            preprocess.PadLeft;

        const int offsetY =
            preprocess.PadTop;

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