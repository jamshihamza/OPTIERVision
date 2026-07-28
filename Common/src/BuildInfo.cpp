#include "pch.h"

#include <optier/BuildInfo.h>

namespace optier
{
    namespace
    {
       
#ifdef _DEBUG
        const std::string kBuildType = "Debug";
#else
        const std::string kBuildType = "Release";
#endif

#ifdef _WIN64
        const std::string kPlatform = "x64";
#else
        const std::string kPlatform = "x86";
#endif

        const std::string kCompiler = "MSVC " + std::to_string(_MSC_VER);

        const std::string kBuildDate = __DATE__;
        const std::string kBuildTime = __TIME__;
    }

  
    const std::string& BuildInfo::BuildType()
    {
        return kBuildType;
    }

    const std::string& BuildInfo::Compiler()
    {
        return kCompiler;
    }

    const std::string& BuildInfo::Platform()
    {
        return kPlatform;
    }

    const std::string& BuildInfo::BuildDate()
    {
        return kBuildDate;
    }

    const std::string& BuildInfo::BuildTime()
    {
        return kBuildTime;
    }
}