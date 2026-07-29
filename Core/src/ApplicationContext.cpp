#include "pch.h"

#include <optier/ApplicationContext.h>

namespace optier
{

    ApplicationContext::ApplicationContext()
    {
    }
    bool ApplicationContext::Initialize()
    {
        if (!m_configuration.Load())
        {
            return false;
        }
        const auto& config = m_configuration.GetConfiguration();
        return true;
    }

    void ApplicationContext::Shutdown()
    {
    }

}