#pragma once

#include <string_view>

namespace optier
{
    class BuildInfo
    {
    public:
        static std::string_view BuildType() noexcept;
        static std::string_view Compiler() noexcept;
        static std::string_view Platform() noexcept;
        static std::string_view BuildDate() noexcept;
        static std::string_view BuildTime() noexcept;

    private:
        BuildInfo() = delete;
    };
}