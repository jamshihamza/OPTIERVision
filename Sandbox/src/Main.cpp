#include "pch.h"
#include <iostream>
#include <chrono>
#include <thread>

#include <optier/Application.h>
#include <optier/ConfigurationManager.h>
#include <optier/Logger.h>
#include <optier/ThreadPool.h>

int main()
{
    optier::Application app;

    if (!app.Initialize())
    {
        std::cout << "Application initialization failed." << std::endl;
        return -1;
    }

    const auto& config =
        app.GetContext()
        .GetConfigurationManager()
        .GetConfiguration();

    std::cout << std::endl;

    std::cout << "Application : "
        << config.Application.Name << std::endl;

    std::cout << "Log Level   : "
        << config.Logging.Level << std::endl;

    std::cout << "RTSP Port   : "
        << config.Network.RtspPort << std::endl;

    std::cout << std::endl;

    optier::Logger::Initialize();

    optier::Logger::Info("Application Started");

    std::cout << std::endl;

    optier::ThreadPool pool(4);

    for (int i = 1; i <= 10; ++i)
    {
        pool.Enqueue(
            [i]()
            {
                optier::Logger::Info(
                    "Task " + std::to_string(i) + " Started");

                std::this_thread::sleep_for(
                    std::chrono::seconds(1));

                optier::Logger::Info(
                    "Task " + std::to_string(i) + " Finished");
            });
    }

    std::this_thread::sleep_for(
        std::chrono::seconds(4));

    pool.Shutdown();

    optier::Logger::Info("Thread Pool Shutdown");

    app.Shutdown();

    return 0;
}