#pragma once

#include <optier/DetectionCollection.h>
#include <optier/VideoFrame.h>

namespace optier
{

    class IObjectDetector
    {
    public:

        virtual ~IObjectDetector() = default;

        virtual DetectionCollection Detect(
            const VideoFrame& frame) = 0;
    };

} // namespace optier