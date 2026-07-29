#pragma once

#include <string>
#include <mutex>
#include <optier/LogLevel.h>

namespace optier
{

    class Logger
    {
    public:

        static void Initialize();

        static void Shutdown();

        static void SetLevel(
            LogLevel level);

        static LogLevel GetLevel();

        static void Trace(
            const std::string& message);

        static void Debug(
            const std::string& message);

        static void Info(
            const std::string& message);

        static void Warning(
            const std::string& message);

        static void Error(
            const std::string& message);

        static void Critical(
            const std::string& message);

    private:

        static void Write(
            LogLevel level,
            const std::string& message);

    private:

        static std::mutex s_mutex;

        static LogLevel s_level;
    };

}