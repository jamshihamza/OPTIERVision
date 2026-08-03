#include "pch.h"

#include <optier/DetectionMapper.h>

namespace optier
{

    std::vector<BoundingBox>
        DetectionMapper::Convert(
            const DetectionCollection& detections)
    {
        std::vector<BoundingBox> boxes;

        boxes.reserve(
            detections.Results.size());

        for (const auto& detection : detections.Results)
        {
            BoundingBox box;

            box.X =
                detection.X;

            box.Y =
                detection.Y;

            box.Width =
                detection.Width;

            box.Height =
                detection.Height;

            box.Label =
                detection.ClassName;

            box.Confidence =
                detection.Confidence;

            //
            // Default rendering color
            //
            box.Color =
                cv::Scalar(0, 255, 0);

            boxes.push_back(
                std::move(box));
        }

        return boxes;
    }

} // namespace optier