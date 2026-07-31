#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include <optier/Device.h>

namespace optier
{

    class DeviceManager
    {
    public:

        DeviceManager() = default;

        ~DeviceManager() = default;

    public:

        bool AddDevice(
            std::shared_ptr<Device> device);

        bool RemoveDevice(
            const std::string& id);

        std::shared_ptr<Device> GetDevice(
            const std::string& id) const;

        std::size_t GetDeviceCount() const;

    private:

        std::unordered_map<
            std::string,
            std::shared_ptr<Device>> m_devices;
    };

}