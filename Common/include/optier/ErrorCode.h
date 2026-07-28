#pragma once

#include <cstdint>

namespace optier
{
    enum class ErrorCode : std::int32_t
    {
        None = 0,

        // General
        Unknown,
        NotImplemented,
        InvalidArgument,
        InvalidOperation,
        OutOfMemory,
        Timeout,

        // File System
        FileNotFound,
        FileAlreadyExists,
        AccessDenied,

        // Configuration
        ConfigurationError,

        // Network
        NetworkError,
        ConnectionFailed,
        ConnectionLost,

        // Device
        DeviceNotFound,
        DeviceBusy,
        DeviceDisconnected,

        // Media
        StreamOpenFailed,
        StreamReadFailed,

        // AI
        AIModelLoadFailed,
        AIInferenceFailed
    };
}