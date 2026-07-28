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

        return true;
    }

    void ApplicationContext::Shutdown()
    {
    }

}