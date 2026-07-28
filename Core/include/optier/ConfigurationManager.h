#pragma once

namespace optier
{

    class ConfigurationManager
    {
    public:
        ConfigurationManager();

        bool Load();

        bool Save();
    };

}