#include "pch.h"

#include <optier/ConfigurationManager.h>

#include <optier/Configuration.h>
#include <optier/FileSystem.h>
#include <optier/JsonDocument.h>
#include <optier/JsonObject.h>

namespace optier
{

    ConfigurationManager::ConfigurationManager()
    {
    }

    bool ConfigurationManager::Load()
    {
        constexpr auto kConfigPath = "config/config.json";

        if (!FileSystem::Exists(kConfigPath))
        {
            return false;
        }

        auto fileResult = FileSystem::ReadTextFile(kConfigPath);

        if (!fileResult.IsSuccess())
        {
            return false;
        }

        JsonDocument document;

        if (!document.Parse(fileResult.Value()))
        {
            return false;
        }

        JsonObject application = document.GetObject("Application");

        if (!application.IsValid())
        {
            return false;
        }

        m_configuration.Application.Name =
            application.GetString("Name");

        JsonObject logging = document.GetObject("Logging");

        if (logging.IsValid())
        {
            m_configuration.Logging.Level =
                logging.GetString("Level");
        }

        JsonObject network = document.GetObject("Network");

        if (network.IsValid())
        {
            m_configuration.Network.RtspPort =
                network.GetInt("RtspPort");
        }

        return true;
    }

    bool ConfigurationManager::Save()
    {
        return true;
    }

    const Configuration&
        ConfigurationManager::GetConfiguration() const
    {
        return m_configuration;
    }

}