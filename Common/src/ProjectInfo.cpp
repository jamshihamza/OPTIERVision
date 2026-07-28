#include "pch.h"

#include <optier/ProjectInfo.h>

namespace
{
    constexpr std::string_view kApplicationName = "OPTIER Vision";
    constexpr std::string_view kCompanyName = "AZOAN Technologies India LLP";
    constexpr std::string_view kWebsite = "https://www.optier.ai";
    constexpr std::string_view kSupportEmail = "support@optier.ai";
    constexpr std::string_view kCopyright =
        "Copyright (c) 2026 AZOAN Technologies India LLP";

    const optier::Version kVersion(1, 0, 0, 1);
}

namespace optier
{
    std::string_view ProjectInfo::ApplicationName() noexcept
    {
        return kApplicationName;
    }

    std::string_view ProjectInfo::CompanyName() noexcept
    {
        return kCompanyName;
    }

    std::string_view ProjectInfo::Website() noexcept
    {
        return kWebsite;
    }

    std::string_view ProjectInfo::SupportEmail() noexcept
    {
        return kSupportEmail;
    }

    std::string_view ProjectInfo::Copyright() noexcept
    {
        return kCopyright;
    }

    const Version& ProjectInfo::Version() noexcept
    {
        return kVersion;
    }
}