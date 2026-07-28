#include "pch.h"

#include <iostream>

#include <optier/Logger.h>

namespace optier
{
    void Logger::Initialize()
    {
    }

    void Logger::Shutdown()
    {
    }

    void Logger::Log(LogLevel level, const std::string& message)
    {
        std::cout << "[" << static_cast<int>(level) << "] "
            << message << std::endl;
    }

    void Logger::Trace(const std::string& message)
    {
        Log(LogLevel::Trace, message);
    }

    void Logger::Debug(const std::string& message)
    {
        Log(LogLevel::Debug, message);
    }

    void Logger::Info(const std::string& message)
    {
        Log(LogLevel::Info, message);
    }

    void Logger::Warning(const std::string& message)
    {
        Log(LogLevel::Warning, message);
    }

    void Logger::Error(const std::string& message)
    {
        Log(LogLevel::Error, message);
    }

    void Logger::Critical(const std::string& message)
    {
        Log(LogLevel::Critical, message);
    }
}