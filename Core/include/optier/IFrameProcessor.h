#pragma once

#include <optier/VideoFrame.h>

namespace optier
{

    class IFrameProcessor
    {
    public:

        virtual ~IFrameProcessor() = default;

    public:

        virtual bool ProcessFrame(
            VideoFrame& frame) = 0;
    };

}