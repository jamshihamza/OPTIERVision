#include "pch.h"

#include <optier/YOLODetectorProcessor.h>
#include <optier/IObjectDetector.h>

#include <string_view>

namespace optier
{

    YOLODetectorProcessor::YOLODetectorProcessor(
        std::shared_ptr<IObjectDetector> detector)
        : m_detector(std::move(detector))
    {
    }

    bool YOLODetectorProcessor::ProcessFrame(
        VideoFrame& frame)
    {
        //
        // Frame skipping
        //
        ++m_processedFrames;

        if ((frame.FrameNumber % m_inferenceInterval) != 0)
        {
            ++m_skippedFrames;

            //
            // Reuse previous detections
            //
			frame.Detections.Results = m_lastDetections;

            return true;
        }

        //
        // Validate detector.
        //
        if (!m_detector)
        {
            return false;
        }

        //
        // Validate image.
        //
        if (!frame.Image)
        {
            return false;
        }

        if (frame.Image->empty())
        {
            return false;
        }

        //
        // Run AI detector.
        //
        const bool result =
            m_detector->Detect(frame);

        if (!result)
        {
            return false;
        }

        //
        // Update detection cache
        //
		m_lastDetections = frame.Detections.Results;

        return true;
    }

    std::string_view YOLODetectorProcessor::Name() const
    {
        return "YOLODetectorProcessor";
    }

} // namespace optier