#pragma once

#include <vector>

#include <optier/DetectionCollection.h>

namespace optier
{

    class DetectionPostProcessor
    {
    public:

        DetectionPostProcessor() = default;

        ~DetectionPostProcessor() = default;

        bool Process(
            DetectionCollection& detections);

    private:

        float m_confidenceThreshold = 0.25f;

        float m_nmsThreshold = 0.45f;
    };

} // namespace optier