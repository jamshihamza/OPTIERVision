#pragma once

namespace optier
{

    enum class StreamState
    {
        Disconnected,

        Connecting,

        Streaming,

        Reconnecting,

        Error
    };

}