#include "pch.h"
#include <optier/ConfigurationManager.h>
#include <optier/Configuration.h>
#include <optier/FileSystem.h>
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