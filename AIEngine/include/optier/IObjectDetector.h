#pragma once

#include <optier/VideoFrame.h>

namespace optier
{

    class IObjectDetector
    {
    public:

        virtual ~IObjectDetector() = default;

        virtual bool Initialize() = 0;

        virtual void Shutdown() = 0;

        virtual bool Detect(
            VideoFrame& frame) = 0;
    };

} // namespace optier