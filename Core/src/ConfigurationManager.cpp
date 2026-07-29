#include "pch.h"
#include <optier/ConfigurationManager.h>
#include <optier/Configuration.h>
namespace optier
{

    ConfigurationManager::ConfigurationManager()
    {
    }

    bool ConfigurationManager::Load()
    {
        m_configuration.Application.Name = "OPTIER Vision Enterprise";
        m_configuration.Logging.Level = "Debug";
        m_configuration.Network.RtspPort = 8554;

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