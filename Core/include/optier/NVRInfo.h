#pragma once

#include <cstdint>

namespace optier
{

    struct NVRInfo
    {
        std::uint32_t ChannelCount = 0;

        std::uint32_t MaxRecordingChannels = 0;

        bool SupportsPlayback = false;

        bool SupportsBackup = false;

        bool SupportsRAID = false;

        std::uint32_t MaxDiskCount = 0;

        std::uint64_t MaxStorageCapacityGB = 0;
    };

}