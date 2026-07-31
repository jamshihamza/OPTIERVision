#pragma once

#include <optier/CameraInfo.h>
#include <optier/CameraStatus.h>
#include <optier/Device.h>

namespace optier
{
	class Camera : public Device
	{
	public:
		Camera(
			const DeviceInfo& deviceInfo,
			const CameraInfo& cameraInfo
		);

		~Camera() override = default;
	public:
		bool Connect() override;
		void Disconnect() override;	
	public:
		const CameraInfo& GetCameraInfo() const;
		const CameraStatus& GetCameraStatus() const;
	protected:
		CameraInfo m_cameraInfo;
		CameraStatus m_cameraStatus;
	};
	}