#pragma once

#include <vector>

#include <optier/BoundingBox.h>
#include <optier/DetectionCollection.h>

namespace optier
{

    class DetectionMapper
    {
    public:

        static std::vector<BoundingBox> Convert(
            const DetectionCollection& detections);
    };

} // namespace optier