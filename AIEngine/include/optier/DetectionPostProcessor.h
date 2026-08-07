#pragma once

#include <vector>

#include <opencv2/core/types.hpp>
#include <optier/DetectionCollection.h>
#include <optier/VideoFrame.h>

namespace optier
{

    class DetectionPostProcessor
    {
    public:

        DetectionPostProcessor() = default;

        bool Process(
            const std::vector<float>& outputTensor,
            VideoFrame& frame);

    private:

        void ApplyNMS(
            VideoFrame& frame);

        void RestoreOriginalCoordinates(
            VideoFrame& frame);

        void ValidateDetections(
            VideoFrame& frame);

    private:

        static constexpr float ConfidenceThreshold = 0.25f;

        static constexpr float NMSThreshold = 0.45f;
    };

} // namespace optier