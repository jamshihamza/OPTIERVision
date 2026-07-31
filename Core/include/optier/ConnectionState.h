#pragma once

namespace optier
{

    enum class ConnectionState
    {
        Disconnected,
        Connecting,
        Connected,
        Reconnecting,
        AuthenticationFailed,
        ConnectionLost
    };

}