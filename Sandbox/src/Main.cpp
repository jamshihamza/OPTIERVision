#include "pch.h"

#include <iostream>

#include <optier/Application.h>

int main()
{
    optier::Application application;

    if (!application.Initialize())
    {
        std::cout << "Initialization Failed\n";
        return -1;
    }

    const auto& config =
        application
        .GetContext()
        .GetConfigurationManager()
        .GetConfiguration();

    std::cout << "Application : "
        << config.Application.Name
        << '\n';

    std::cout << "Log Level   : "
        << config.Logging.Level
        << '\n';

    std::cout << "RTSP Port   : "
        << config.Network.RtspPort
        << '\n';

    application.Shutdown();

    return 0;
}