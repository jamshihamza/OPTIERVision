#pragma once

#include <string>
#include <cstdint>

namespace optier
{
    class Version
    {
    public:
         Version(std::uint16_t major,
            std::uint16_t minor,
            std::uint16_t patch,
            std::uint16_t build) noexcept;

        std::uint16_t Major() const noexcept;
        std::uint16_t Minor() const noexcept;
        std::uint16_t Patch() const noexcept;
        std::uint16_t Build() const noexcept;

        std::string ToString() const;

        bool operator==(const Version& other) const noexcept;
        bool operator!=(const Version& other) const noexcept;

    private:
        std::uint16_t m_major;
        std::uint16_t m_minor;
        std::uint16_t m_patch;
        std::uint16_t m_build;
    };
}