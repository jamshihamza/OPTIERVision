#pragma once

#include <optier/DetectionCollection.h>

namespace optier
{

    class NonMaximumSuppression
    {
    public:

        NonMaximumSuppression() = default;

        //
        // Removes duplicate detections.
        //
        void Apply(
            DetectionCollection& detections);

    private:

        //
        // Computes Intersection over Union.
        //
        float IoU(
            const DetectionResult& lhs,
            const DetectionResult& rhs) const;

    private:

        //
        // Suppress detections whose IoU
        // exceeds this threshold.
        //
        static constexpr float IoUThreshold = 0.45f;
    };

} // namespace optier