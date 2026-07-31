#pragma once

#include <optier/Device.h>
#include <optier/NVRInfo.h>
#include <optier/NVRStatus.h>

namespace optier
{

    class NVR : public Device
    {
    public:

        NVR(
            const DeviceInfo& deviceInfo,
            const NVRInfo& nvrInfo);

        ~NVR() override = default;

    public:

        bool Connect() override;

        void Disconnect() override;

    public:

        const NVRInfo& GetNVRInfo() const;

        const NVRStatus& GetNVRStatus() const;

    private:

        NVRInfo m_nvrInfo;

        NVRStatus m_nvrStatus;
    };

}