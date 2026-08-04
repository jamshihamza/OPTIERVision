#include "pch.h"

#include <optier/DetectionMapperProcessor.h>
#include <optier/DetectionMapper.h>

namespace optier
{

    bool DetectionMapperProcessor::ProcessFrame(
        VideoFrame& frame)
    {
        //
        // Convert AI detections into rendering objects
        //
        frame.BoundingBoxes =
            DetectionMapper::Convert(
                frame.Detections);

        return true;
    }

} // namespace optier