#include "pch.h"

#include <iostream>

#include <optier/Application.h>
#include <optier/Logger.h>
int main()
{
    using namespace optier;
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

    Logger::Initialize();

    Logger::Trace("Trace Message");
    Logger::Debug("Debug Message");
    Logger::Info("Application Started");
    Logger::Warning("Camera Offline");
    Logger::Error("Unable to Connect");
    Logger::Critical("System Failure");
    return 0;
}