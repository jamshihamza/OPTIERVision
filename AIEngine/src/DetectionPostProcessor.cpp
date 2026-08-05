#include "pch.h"

#include <algorithm>

#include <optier/DetectionPostProcessor.h>

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

        //
        // YOLOv8 output
        //
        constexpr int BoxCount = 8400;
        constexpr int FeatureCount = 84;

        if (outputTensor.size() < BoxCount * FeatureCount)
        {
            return false;
        }

        //
        // Layout:
        //
        // 0  -> x
        // 1  -> y
        // 2  -> w
        // 3  -> h
        // 4..83 -> class scores
        //
        for (int i = 0; i < BoxCount; ++i)
        {
            float x =
                outputTensor[0 * BoxCount + i];

            float y =
                outputTensor[1 * BoxCount + i];

            float w =
                outputTensor[2 * BoxCount + i];

            float h =
                outputTensor[3 * BoxCount + i];

            float bestScore = 0.0f;
            int bestClass = -1;

            //
            // Find highest class score
            //
            for (int c = 4; c < FeatureCount; ++c)
            {
                float score =
                    outputTensor[c * BoxCount + i];

                if (score > bestScore)
                {
                    bestScore = score;
                    bestClass = c - 4;
                }
            }

            //
            // Confidence threshold
            //
            if (bestScore < ConfidenceThreshold)
            {
                continue;
            }

            DetectionResult detection;

            detection.ClassId =
                static_cast<std::uint32_t>(bestClass);

            detection.ClassName =
                std::to_string(bestClass);

            detection.Confidence =
                bestScore;

            detection.X =
                static_cast<int>(x - w / 2.0f);

            detection.Y =
                static_cast<int>(y - h / 2.0f);

            detection.Width =
                static_cast<int>(w);

            detection.Height =
                static_cast<int>(h);

            detections.Results.push_back(
                std::move(detection));
        }

        return true;
    }

} // namespace optier