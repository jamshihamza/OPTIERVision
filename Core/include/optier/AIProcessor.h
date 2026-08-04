#pragma once

#include <memory>

#include <optier/IFrameProcessor.h>
#include <optier/IObjectDetector.h>

namespace optier
{

    class AIProcessor final
        : public IFrameProcessor
    {
    public:

        explicit AIProcessor(
            std::unique_ptr<IObjectDetector> detector);

        bool ProcessFrame(
            VideoFrame& frame) override;

    private:

        std::unique_ptr<IObjectDetector> m_detector;
    };

} // namespace optier