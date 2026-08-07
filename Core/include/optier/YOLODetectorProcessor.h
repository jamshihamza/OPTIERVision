#pragma once

#include <memory>

#include <optier/IFrameProcessor.h>

namespace optier
{

    class IObjectDetector;

    class YOLODetectorProcessor final
        : public IFrameProcessor
    {
    public:

        explicit YOLODetectorProcessor(
            std::shared_ptr<IObjectDetector> detector);

        bool ProcessFrame(
            VideoFrame& frame) override;

        std::string_view Name() const override;

    private:

        std::shared_ptr<IObjectDetector> m_detector;
    };

} // namespace optier