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
        DetectionCollection& detections)
    {
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

        constexpr float ConfidenceThreshold = 0.25f;

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
        ApplyNMS(detections);
        std::cout << "\n========================================\n";
        std::cout << "YOLO DETECTIONS\n";
        std::cout << "========================================\n";

        std::cout
            << "Total Detections : "
            << detections.Results.size()
            << "\n";

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
        DetectionCollection& detections)
    {
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
} // namespace optier