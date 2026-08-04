#pragma once

#include <optier/IFrameProcessor.h>

namespace optier
{

    class DetectionMapperProcessor final
        : public IFrameProcessor
    {
    public:

        bool ProcessFrame(
            VideoFrame& frame) override;
    };

} // namespace optier