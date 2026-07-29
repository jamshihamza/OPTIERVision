#pragma once
#include <optier/Configuration.h>
namespace optier
{

    class ConfigurationManager
    {
    public:

        ConfigurationManager();

        bool Load();

        bool Save();

        const Configuration& GetConfiguration() const;

    private:

        Configuration m_configuration;
    };

}