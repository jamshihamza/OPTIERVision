#pragma once

#include <optier/ConfigurationManager.h>

namespace optier
{

    class ApplicationContext
    {
    public:

        ApplicationContext();

        bool Initialize();

        void Shutdown();

        const ConfigurationManager& GetConfigurationManager() const;

    private:

        ConfigurationManager m_configuration;
    };

}