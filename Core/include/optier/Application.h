#pragma once

#include <optier/ApplicationContext.h>

namespace optier
{

    class Application
    {
    public:
        Application();
        virtual ~Application();

        bool Initialize();
        void Run();
        void Shutdown();

    private:
        bool m_initialized = false;

        ApplicationContext m_context;
    };

}