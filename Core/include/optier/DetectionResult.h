#pragma once

#include <cstdint>
#include <string>

namespace optier
{

    struct DetectionResult
    {
        //
        // Object Identity
        //
        std::uint32_t ClassId = 0;

        std::string ClassName;

        //
        // Detection Score
        //
        float Confidence = 0.0f;

        //
        // Bounding Rectangle
        //
        int X = 0;

        int Y = 0;

        int Width = 0;

        int Height = 0;
    };

} // namespace optier