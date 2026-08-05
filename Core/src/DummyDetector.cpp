#include "pch.h"

#include <optier/DummyDetector.h>

namespace optier
{

    bool DummyDetector::Initialize()
    {
        return true;
    }

    void DummyDetector::Shutdown()
    {
    }

    bool DummyDetector::Detect(
        VideoFrame& frame)
    {
        (void)frame;

        //
        // No detections yet.
        //
        return true;
    }

} // namespace optier