#pragma once

#include <optier/IObjectDetector.h>

namespace optier
{

    class DummyDetector final
        : public IObjectDetector
    {
    public:

        DetectionCollection Detect(
            const VideoFrame& frame) override;
    };

} // namespace optier