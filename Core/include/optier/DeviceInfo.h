#pragma once

#include <cstdint>
#include <string>

namespace optier
{

    struct DeviceInfo
    {
        std::string Id;

        std::string Name;

        std::string IPAddress;

        std::uint16_t Port = 0;

        std::string Username;

        std::string Password;

        std::string Manufacturer;

        std::string Model;

        std::string FirmwareVersion;

        std::string MacAddress;
    };

}