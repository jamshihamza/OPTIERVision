#pragma once

#include <memory>
#include <vector>
#include <optier/IFrameProcessor.h>

namespace optier
{

    class IObjectDetector;

    struct DetectionResult;

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

        //
        //Performance Optimization
        //

        std::uint32_t m_inferenceInterval{4};

		std::uint64_t m_processedFrames{ 0 };

		std::uint64_t m_skippedFrames{ 0 };

        //
		// Detection Persistence Cache
        //
		std::vector<DetectionResult> m_lastDetections;
    };

} // namespace optier