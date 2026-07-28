#include "pch.h"

#include <optier/BuildInfo.h>

namespace
{
#ifdef _DEBUG
    constexpr std::string_view kBuildType = "Debug";
#else
    constexpr std::string_view kBuildType = "Release";
#endif

#ifdef _WIN64
    constexpr std::string_view kPlatform = "x64";
#else
    constexpr std::string_view kPlatform = "x86";
#endif

#ifdef _MSC_VER
    constexpr std::string_view kCompiler = "MSVC";
#else
    constexpr std::string_view kCompiler = "Unknown";
#endif

    constexpr std::string_view kBuildDate = __DATE__;
    constexpr std::string_view kBuildTime = __TIME__;
}

namespace optier
{
    std::string_view BuildInfo::BuildType() noexcept
    {
        return kBuildType;
    }

    std::string_view BuildInfo::Compiler() noexcept
    {
        return kCompiler;
    }

    std::string_view BuildInfo::Platform() noexcept
    {
        return kPlatform;
    }

    std::string_view BuildInfo::BuildDate() noexcept
    {
        return kBuildDate;
    }

    std::string_view BuildInfo::BuildTime() noexcept
    {
        return kBuildTime;
    }
}