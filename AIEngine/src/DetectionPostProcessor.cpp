#include "pch.h"

#include <optier/DetectionPostProcessor.h>

namespace optier
{

    bool DetectionPostProcessor::Process(
        DetectionCollection& detections)
    {
        //
        // TODO:
        //
        // 1. Decode YOLO output tensor.
        // 2. Filter detections by confidence.
        // 3. Apply Non-Maximum Suppression (NMS).
        // 4. Convert to DetectionResult objects.
        // 5. Store inside DetectionCollection.
        //

        (void)detections;

        return true;
    }

} // namespace optier