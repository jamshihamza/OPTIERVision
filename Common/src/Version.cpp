#include "pch.h"

#include <sstream>

#include <optier/Version.h>

namespace optier
{
    Version::Version(std::uint16_t major,
        std::uint16_t minor,
        std::uint16_t patch,
        std::uint16_t build) noexcept
        : m_major(major)
        , m_minor(minor)
        , m_patch(patch)
        , m_build(build)
    {
    }

    std::uint16_t Version::Major() const noexcept
    {
        return m_major;
    }

    std::uint16_t Version::Minor() const noexcept
    {
        return m_minor;
    }

    std::uint16_t Version::Patch() const noexcept
    {
        return m_patch;
    }

    std::uint16_t Version::Build() const noexcept
    {
        return m_build;
    }

    std::string Version::ToString() const
    {
        std::ostringstream stream;

        stream << m_major << '.'
            << m_minor << '.'
            << m_patch << '.'
            << m_build;

        return stream.str();
    }

    bool Version::operator==(const Version& other) const noexcept
    {
        return m_major == other.m_major &&
            m_minor == other.m_minor &&
            m_patch == other.m_patch &&
            m_build == other.m_build;
    }

    bool Version::operator!=(const Version& other) const noexcept
    {
        return !(*this == other);
    }
}