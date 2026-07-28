#pragma once

#include <string_view>

#include <optier/Version.h>

namespace optier
{
    class ProjectInfo
    {
    public:
        static std::string_view ApplicationName() noexcept;
        static std::string_view CompanyName() noexcept;
        static std::string_view Website() noexcept;
        static std::string_view SupportEmail() noexcept;
        static std::string_view Copyright() noexcept;

        static const Version& Version() noexcept;

    private:
        ProjectInfo() = delete;
    };
}