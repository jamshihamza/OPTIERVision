#pragma once

#include <vector>

#include <opencv2/core/types.hpp>
#include <optier/DetectionCollection.h>

namespace optier
{

    class DetectionPostProcessor
    {
    public:

        DetectionPostProcessor() = default;

        bool Process(
            const std::vector<float>& outputTensor,
            DetectionCollection& detections);

    private:

        void ApplyNMS(
            DetectionCollection& detections);
    private:

        static constexpr float ConfidenceThreshold = 0.25f;

        static constexpr float NMSThreshold = 0.45f;
    };

} // namespace optier