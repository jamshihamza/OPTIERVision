#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include <optier/AICapability.h>

namespace optier
{

    struct CameraInfo
    {
        std::string RtspUrl;

        std::string MainStreamUrl;

        std::string SubStreamUrl;

        std::string SnapshotUrl;

        bool SupportsPTZ = false;

        bool SupportsAudio = false;

        std::uint32_t MaxWidth = 0;

        std::uint32_t MaxHeight = 0;

        std::uint32_t MaxFPS = 0;

        std::vector<AICapability> SupportedAICapabilities;
    };

}