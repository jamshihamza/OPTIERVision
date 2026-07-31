#pragma once

#include <cstdint>

#include <optier/ConnectionState.h>

namespace optier
{

    struct NVRStatus
    {
        ConnectionState ConnectionState =
            ConnectionState::Disconnected;

        bool IsRecording = false;

        bool IsPlaybackActive = false;

        std::uint32_t ActiveChannels = 0;

        std::uint32_t DiskUsagePercent = 0;

        std::uint32_t CpuUsagePercent = 0;

        std::uint32_t Temperature = 0;
    };

}