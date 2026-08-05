#include "pch.h"

#include <optier/YOLODetectorProcessor.h>
#include <optier/IObjectDetector.h>


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
        return m_detector->Detect(frame);
    }

} // namespace optier