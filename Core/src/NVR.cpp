#include "pch.h"

#include <optier/NVR.h>

namespace optier
{

    NVR::NVR(
        const DeviceInfo& deviceInfo,
        const NVRInfo& nvrInfo)
    {
        m_info = deviceInfo;
        m_nvrInfo = nvrInfo;
    }

    bool NVR::Connect()
    {
        m_connectionState = ConnectionState::Connected;
        m_nvrStatus.ConnectionState = ConnectionState::Connected;

        return true;
    }

    void NVR::Disconnect()
    {
        m_connectionState = ConnectionState::Disconnected;
        m_nvrStatus.ConnectionState = ConnectionState::Disconnected;
    }

    const NVRInfo& NVR::GetNVRInfo() const
    {
        return m_nvrInfo;
    }

    const NVRStatus& NVR::GetNVRStatus() const
    {
        return m_nvrStatus;
    }

}