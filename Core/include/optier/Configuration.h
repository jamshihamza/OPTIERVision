#pragma once

#include <string>

namespace optier
{

    struct LoggingSettings
    {
        std::string Level = "Info";
    };

    struct NetworkSettings
    {
        int RtspPort = 554;
    };

    struct ApplicationSettings
    {
        std::string Name = "OPTIER Vision";
    };

    class Configuration
    {
    public:
        ApplicationSettings Application;
        LoggingSettings Logging;
        NetworkSettings Network;
    };

}