#pragma once

#include <cstdint>

#include <optier/ConnectionState.h>

namespace optier
{

    struct CameraStatus
    {
        ConnectionState ConnectionState =
            ConnectionState::Disconnected;

        bool IsStreaming = false;

        bool IsRecording = false;

        bool IsAIRunning = false;

        std::uint32_t CurrentFPS = 0;

        std::uint32_t CurrentBitrate = 0;

        std::uint64_t DroppedFrames = 0;
    };

}
