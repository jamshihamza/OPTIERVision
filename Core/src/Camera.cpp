#include "pch.h"

#include <optier/Camera.h>

namespace optier
{

    Camera::Camera(const DeviceInfo& deviceInfo,
        const CameraInfo& cameraInfo)
    {
		m_info = deviceInfo;
		m_cameraInfo = cameraInfo;
    }

    bool Camera::Connect()
    {
        m_connectionState = ConnectionState::Connected;
        m_cameraStatus.ConnectionState = ConnectionState::Connected;

        return true;
    }

    void Camera::Disconnect()
    {
        m_connectionState = ConnectionState::Disconnected;
        m_cameraStatus.ConnectionState = ConnectionState::Disconnected;
    }

    const CameraInfo& Camera::GetCameraInfo() const
    {
        return m_cameraInfo;
    }

    const CameraStatus& Camera::GetCameraStatus() const
    {
        return m_cameraStatus;
    }

}