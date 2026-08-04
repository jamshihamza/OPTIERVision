#include "pch.h"

#include <utility>

#include <optier/AIProcessor.h>

namespace optier
{

    AIProcessor::AIProcessor(
        std::unique_ptr<IObjectDetector> detector)
        : m_detector(std::move(detector))
    {
    }

    bool AIProcessor::ProcessFrame(
        VideoFrame& frame)
    {
        //
        // Validate detector
        //
        if (!m_detector)
        {
            return false;
        }

        //
        // Run AI detection and store results
        // directly inside the frame.
        //
        frame.Detections =
            m_detector->Detect(frame);

        return true;
    }

} // namespace optier