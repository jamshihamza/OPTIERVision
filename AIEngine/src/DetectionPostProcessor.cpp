#include "pch.h"

#include <algorithm>

#include <opencv2/dnn/dnn.hpp>
#include <optier/DetectionPostProcessor.h>
#include <optier/COCOClasses.h>
#include <iostream>

namespace optier
{

    bool DetectionPostProcessor::Process(
        const std::vector<float>& outputTensor,
        VideoFrame& frame)
    {
        DetectionCollection& detections =
            frame.Detections;
        detections.Results.clear();

        if (outputTensor.empty())
        {
            return false;
        }

        constexpr int PredictionCount = 8400;
        constexpr int FeatureCount = 84;
        constexpr int ClassCount = 80;

        if (outputTensor.size() !=
            PredictionCount * FeatureCount)
        {
            return false;
        }

     

        //
        // Tensor Layout
        //
        // Row 0  -> x
        // Row 1  -> y
        // Row 2  -> w
        // Row 3  -> h
        // Row 4  -> class 0
        // ...
        // Row 83 -> class 79
        //
        for (int prediction = 0;
            prediction < PredictionCount;
            ++prediction)
        {
            float centerX =
                outputTensor[0 * PredictionCount + prediction];

            float centerY =
                outputTensor[1 * PredictionCount + prediction];

            float width =
                outputTensor[2 * PredictionCount + prediction];

            float height =
                outputTensor[3 * PredictionCount + prediction];

            float bestScore = 0.0f;

            int bestClass = -1;

            //
            // Search all 80 classes
            //
            for (int cls = 0;
                cls < ClassCount;
                ++cls)
            {
                float score =
                    outputTensor[
                        (cls + 4) * PredictionCount +
                            prediction];

                if (score > bestScore)
                {
                    bestScore = score;
                    bestClass = cls;
                }
            }

            if (bestScore < ConfidenceThreshold)
            {
                continue;
            }

            DetectionResult result;

            result.ClassId =
                static_cast<std::uint32_t>(
                    bestClass);

            result.ClassName =
                std::string(
                    COCOClasses::Names[bestClass]);

            result.Confidence =
                bestScore;

            //
            // Convert
            // Center → Top Left
            //
            result.X =
                static_cast<int>(
                    centerX - width * 0.5f);

            result.Y =
                static_cast<int>(
                    centerY - height * 0.5f);

            result.Width =
                static_cast<int>(width);

            result.Height =
                static_cast<int>(height);

            detections.Results.push_back(
                std::move(result));
        }
        
        RestoreOriginalCoordinates(frame);

		ValidateDetections(frame);

        ApplyNMS(frame);

       /* std::cout << "\n========================================\n";
        std::cout << "YOLO DETECTIONS\n";
        std::cout << "========================================\n";

        std::cout
            << "Total Detections : "
            << detections.Results.size()
            << "\n";*/

        std::size_t count =
            std::min<std::size_t>(
                detections.Results.size(),
                10);

        for (std::size_t i = 0; i < count; ++i)
        {
            const auto& d =
                detections.Results[i];

            std::cout
                << "[" << i << "] "
                << d.ClassName
                << " (" << d.ClassId << ")"
                << "  Confidence=" << d.Confidence
                << "  Box=("
                << d.X << ", "
                << d.Y << ", "
                << d.Width << ", "
                << d.Height << ")\n";
        }

        std::cout << "========================================\n";
        return true;
    }

    void DetectionPostProcessor::ApplyNMS(
        VideoFrame& frame)
    {
        DetectionCollection& detections =
            frame.Detections;
        if (detections.Results.empty())
        {
            return;
        }

        std::vector<cv::Rect> boxes;
        std::vector<float> scores;

        boxes.reserve(detections.Results.size());
        scores.reserve(detections.Results.size());

        for (const auto& detection : detections.Results)
        {
            boxes.emplace_back(
                detection.X,
                detection.Y,
                detection.Width,
                detection.Height);

            scores.push_back(
                detection.Confidence);
        }

        std::vector<int> indices;

        cv::dnn::NMSBoxes(
            boxes,
            scores,
            ConfidenceThreshold,
            NMSThreshold,
            indices);

        DetectionCollection filtered;

        filtered.FrameNumber =
            detections.FrameNumber;

        filtered.Timestamp =
            detections.Timestamp;

        filtered.InferenceTime =
            detections.InferenceTime;

        for (int index : indices)
        {
            filtered.Results.push_back(
                detections.Results[index]);
        }

        detections = std::move(filtered);
    }

    void DetectionPostProcessor::RestoreOriginalCoordinates(
        VideoFrame& frame)
    {
        DetectionCollection& detections =
            frame.Detections;

        const PreprocessMetadata& preprocess =
            frame.Preprocess;

        //
        // Validate scale.
        //
        if (preprocess.Scale <= 0.0f)
        {
            return;
        }

        const float inverseScale =
            1.0f / preprocess.Scale;

        for (auto& detection : detections.Results)
        {
            //
            // Remove letterbox padding.
            //
            detection.X -= preprocess.PadLeft;
            detection.Y -= preprocess.PadTop;

            //
            // Scale back to original image.
            //
            detection.X =
                static_cast<int>(
                    detection.X * inverseScale);

            detection.Y =
                static_cast<int>(
                    detection.Y * inverseScale);

            detection.Width =
                static_cast<int>(
                    detection.Width * inverseScale);

            detection.Height =
                static_cast<int>(
                    detection.Height * inverseScale);

            //
            // Clamp left/top.
            //
            detection.X =
                std::max(
                    0,
                    detection.X);

            detection.Y =
                std::max(
                    0,
                    detection.Y);

            //
            // Clamp width.
            //
            if (detection.X + detection.Width >
                preprocess.OriginalWidth)
            {
                detection.Width =
                    preprocess.OriginalWidth -
                    detection.X;
            }

            //
            // Clamp height.
            //
            if (detection.Y + detection.Height >
                preprocess.OriginalHeight)
            {
                detection.Height =
                    preprocess.OriginalHeight -
                    detection.Y;
            }
        }
    }

    void DetectionPostProcessor::ValidateDetections(
        VideoFrame& frame)
    {
        DetectionCollection& detections =
            frame.Detections;

        const auto& preprocess =
            frame.Preprocess;

        auto& results =
            detections.Results;

        results.erase(
            std::remove_if(
                results.begin(),
                results.end(),
                [&](const DetectionResult& detection)
                {
                    //
                    // Invalid size
                    //
                    if (detection.Width <= 0 ||
                        detection.Height <= 0)
                    {
                        return true;
                    }

                    //
                    // Image boundary
                    //
                    if (detection.X >= preprocess.OriginalWidth ||
                        detection.Y >= preprocess.OriginalHeight)
                    {
                        return true;
                    }

                    //
                    // Extremely large boxes
                    //
                    if (detection.Width >
                        preprocess.OriginalWidth * 0.90f)
                    {
                        return true;
                    }

                    if (detection.Height >
                        preprocess.OriginalHeight * 0.90f)
                    {
                        return true;
                    }

                    return false;
                }),
            results.end());
    }

} // namespace optier