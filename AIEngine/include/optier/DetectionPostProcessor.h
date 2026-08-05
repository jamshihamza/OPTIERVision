#pragma once

#include <vector>

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

        static constexpr float ConfidenceThreshold = 0.25f;
    };

} // namespace optier