#include "pch.h"

#include <optier/Logger.h>

#include <iostream>

namespace optier
{
    std::mutex Logger::s_mutex;
    LogLevel Logger::s_level = LogLevel::Info;

    void Logger::Initialize()
    {
    }

    void Logger::Shutdown()
    {
    }

    void Logger::SetLevel(LogLevel level)
    {
        s_level = level;
    }

    LogLevel Logger::GetLevel()
    {
        return s_level;
    }

    void Logger::Trace(const std::string& message)
    {
        Write(LogLevel::Trace, message);
    }

    void Logger::Debug(const std::string& message)
    {
        Write(LogLevel::Debug, message);
    }

    void Logger::Info(const std::string& message)
    {
        Write(LogLevel::Info, message);
    }

    void Logger::Warning(const std::string& message)
    {
        Write(LogLevel::Warning, message);
    }

    void Logger::Error(const std::string& message)
    {
        Write(LogLevel::Error, message);
    }

    void Logger::Critical(const std::string& message)
    {
        Write(LogLevel::Critical, message);
    }

    void Logger::Write(
        LogLevel level,
        const std::string& message)
    {
        std::lock_guard<std::mutex> lock(s_mutex);
        if (level < s_level)
        {
            return;
        }

        switch (level)
        {
        case LogLevel::Trace:
            std::cout << "[TRACE] ";
            break;

        case LogLevel::Debug:
            std::cout << "[DEBUG] ";
            break;

        case LogLevel::Info:
            std::cout << "[INFO ] ";
            break;

        case LogLevel::Warning:
            std::cout << "[WARN ] ";
            break;

        case LogLevel::Error:
            std::cout << "[ERROR] ";
            break;

        case LogLevel::Critical:
            std::cout << "[FATAL] ";
            break;
        }

        std::cout << message << std::endl;
    }

}