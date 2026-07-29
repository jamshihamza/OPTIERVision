#include "pch.h"

#include <optier/ApplicationContext.h>

namespace optier
{

    ApplicationContext::ApplicationContext()
    {
    }

    bool ApplicationContext::Initialize()
    {
        return m_configuration.Load();
    }

    void ApplicationContext::Shutdown()
    {
    }

    const ConfigurationManager&
        ApplicationContext::GetConfigurationManager() const
    {
        return m_configuration;
    }

}