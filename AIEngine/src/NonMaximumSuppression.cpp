#include "pch.h"

#include <algorithm>
#include <optier/NonMaximumSuppression.h>


namespace optier
{

    void NonMaximumSuppression::Apply(
        DetectionCollection& detections)
    {
        //
        // Nothing to do.
        //
        if (detections.Results.size() <= 1)
        {
            return;
        }

        //
        // Sort detections by confidence.
        //
        std::sort(
            detections.Results.begin(),
            detections.Results.end(),
            [](const DetectionResult& lhs,
                const DetectionResult& rhs)
            {
                return lhs.Confidence > rhs.Confidence;
            });

        std::vector<DetectionResult> filtered;

        std::vector<bool> suppressed(
            detections.Results.size(),
            false);

        //
        // Process detections.
        //
        for (std::size_t i = 0;
            i < detections.Results.size();
            ++i)
        {
            if (suppressed[i])
            {
                continue;
            }

            //
            // Keep highest confidence detection.
            //
            filtered.push_back(
                detections.Results[i]);

            //
            // Compare with remaining detections.
            //
            for (std::size_t j = i + 1;
                j < detections.Results.size();
                ++j)
            {
                if (suppressed[j])
                {
                    continue;
                }

                //
                // Suppress only detections
                // belonging to the same class.
                //
                if (detections.Results[i].ClassId !=
                    detections.Results[j].ClassId)
                {
                    continue;
                }

                float overlap =
                    IoU(
                        detections.Results[i],
                        detections.Results[j]);

                if (overlap > IoUThreshold)
                {
                    suppressed[j] = true;
                }
            }
        }

        detections.Results =
            std::move(filtered);
    }

    float NonMaximumSuppression::IoU(
        const DetectionResult& lhs,
        const DetectionResult& rhs) const
    {
        //
        // Rectangle A
        //
        const int leftA = lhs.X;
        const int topA = lhs.Y;
        const int rightA = lhs.X + lhs.Width;
        const int bottomA = lhs.Y + lhs.Height;

        //
        // Rectangle B
        //
        const int leftB = rhs.X;
        const int topB = rhs.Y;
        const int rightB = rhs.X + rhs.Width;
        const int bottomB = rhs.Y + rhs.Height;

        //
        // Intersection rectangle
        //
        const int left =
            std::max(leftA, leftB);

        const int top =
            std::max(topA, topB);

        const int right =
            std::min(rightA, rightB);

        const int bottom =
            std::min(bottomA, bottomB);

        //
        // No overlap
        //
        if (right <= left || bottom <= top)
        {
            return 0.0f;
        }

        //
        // Areas
        //
        const float intersectionArea =
            static_cast<float>(
                (right - left) *
                (bottom - top));

        const float areaA =
            static_cast<float>(
                lhs.Width *
                lhs.Height);

        const float areaB =
            static_cast<float>(
                rhs.Width *
                rhs.Height);

        const float unionArea =
            areaA +
            areaB -
            intersectionArea;

        if (unionArea <= 0.0f)
        {
            return 0.0f;
        }

        return
            intersectionArea /
            unionArea;
    }

} // namespace optier