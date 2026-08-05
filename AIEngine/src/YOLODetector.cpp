#include "pch.h"

#include <optier/YOLODetector.h>

namespace optier
{

    YOLODetector::YOLODetector(
        const std::string& modelPath)
        : m_modelLoader(modelPath)
    {
    }

    bool YOLODetector::Initialize()
    {
        return m_modelLoader.Load();
    }

    void YOLODetector::Shutdown()
    {
        m_modelLoader.Unload();
    }

    bool YOLODetector::Detect(
        VideoFrame& frame)
    {
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
        // Temporary implementation.
        // Real inference will be added next.
        //
        return true;
    }

} // namespace optier