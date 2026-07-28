#pragma once
#pragma once

#include <string>

#include <optier/Version.h>

namespace optier
{
    class BuildInfo
    {
    public:
        static const std::string& ApplicationName();
        static const std::string& CompanyName();

        static const Version& ApplicationVersion();

        static const std::string& BuildType();
        static const std::string& Compiler();
        static const std::string& Platform();

        static const std::string& BuildDate();
        static const std::string& BuildTime();

    private:
        BuildInfo() = delete;
    };
}