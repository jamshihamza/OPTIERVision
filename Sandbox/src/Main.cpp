#include "pch.h"
#include <iostream>
#include <chrono>
#include <thread>

#include <optier/Application.h>
#include <optier/ConfigurationManager.h>
#include <optier/Logger.h>
#include <optier/ThreadPool.h>
#include <optier/Event.h>
#include <optier/EventDispatcher.h>

int main()
{
    class TestEvent : public optier::Event
    {
    public:
        std::string GetName() const override
        {
            return "TestEvent";
        }
    };

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

    optier::EventDispatcher dispatcher;

    dispatcher.Subscribe(
        [](const optier::Event&)
        {
            optier::Logger::Info(
                "Recorder Module Received Event");
        });

    dispatcher.Subscribe(
        [](const optier::Event&)
        {
            optier::Logger::Info(
                "Notification Module Received Event");
        });

    dispatcher.Subscribe(
        [](const optier::Event&)
        {
            optier::Logger::Info(
                "UI Module Received Event");
        });

    TestEvent event;

    dispatcher.Dispatch(event);
    return 0;
}