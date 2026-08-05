#pragma once

#include <optier/IObjectDetector.h>

namespace optier
{

    class DummyDetector final
        : public IObjectDetector
    {
    public:

        DummyDetector() = default;

        bool Initialize() override;

        void Shutdown() override;

        bool Detect(
            VideoFrame& frame) override;
    };

} // namespace optier