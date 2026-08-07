#pragma once

#include <optier/VideoFrame.h>
#include <string_view>

namespace optier
{

    class IFrameProcessor
    {
    public:

        virtual ~IFrameProcessor() = default;

  
        virtual bool ProcessFrame(
            VideoFrame& frame) = 0;

        virtual std::string_view Name() const = 0;
    };

}