#pragma once

#include <optier/ConnectionState.h>
#include <optier/DeviceInfo.h>

namespace optier
{

    class Device
    {
    public:

        Device();

        virtual ~Device() = default;

    public:

        virtual bool Connect() = 0;

        virtual void Disconnect() = 0;

    public:

        const DeviceInfo& GetInfo() const;

        ConnectionState GetConnectionState() const;

    protected:

        DeviceInfo m_info;

        ConnectionState m_connectionState;
    };

}