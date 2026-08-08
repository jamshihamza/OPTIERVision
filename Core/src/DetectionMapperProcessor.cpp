#include "pch.h"

#include <optier/DetectionMapperProcessor.h>
#include <optier/DetectionMapper.h>
#include <string_view>

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

    std::string_view optier::DetectionMapperProcessor::Name() const
    {
        return "DetectionMapperProcessor";
    }
} // namespace optier