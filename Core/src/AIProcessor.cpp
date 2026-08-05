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
        // Validate frame
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
        // Detector populates frame.Detections.
        //
        return m_detector->Detect(frame);
    }

} // namespace optier