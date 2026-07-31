#include "pch.h"

#include <optier/Device.h>

namespace optier
{

    Device::Device()
        : m_connectionState(ConnectionState::Disconnected)
    {
    }

    const DeviceInfo& Device::GetInfo() const
    {
        return m_info;
    }

    ConnectionState Device::GetConnectionState() const
    {
        return m_connectionState;
    }

}