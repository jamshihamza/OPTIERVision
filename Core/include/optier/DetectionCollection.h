#pragma once

#include <chrono>
#include <cstdint>
#include <vector>

#include <optier/DetectionResult.h>

namespace optier
{

    struct DetectionCollection
    {
        //
        // Frame Information
        //
        std::uint64_t FrameNumber = 0;

        std::chrono::steady_clock::time_point Timestamp;

        //
        // AI Performance
        //
        std::chrono::milliseconds InferenceTime{ 0 };

        //
        // Detection Results
        //
        std::vector<DetectionResult> Results;
    };

} // namespace optier