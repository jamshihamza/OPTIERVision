#include "pch.h"
#include <optier/DeviceManager.h>

namespace optier
{
	bool DeviceManager::AddDevice(
		std::shared_ptr<Device> device)
	{
		if (device == nullptr)
		{
			return false;
		}
		const std::string& id = device->GetInfo().Id;

		auto resut = m_devices.emplace(id, device);

		return resut.second;
	}
	bool DeviceManager::RemoveDevice(
		const std::string& id)
	{
		return m_devices.erase(id) > 0;
	}

	std::shared_ptr<Device> DeviceManager::GetDevice(
		const std::string& id) const
	{
		auto it = m_devices.find(id);
		if (it == m_devices.end())
		{
			return nullptr;
		}
		return it->second;
	}
	std::size_t DeviceManager::GetDeviceCount() const
	{
		return m_devices.size();
	}
}