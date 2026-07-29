#include "pch.h"

#include <optier/Application.h>

namespace optier
{
    Application::Application()
        : m_initialized(false)
    {
    }

    Application::~Application()
    {
    }

    bool Application::Initialize()
    {
        if (!m_context.Initialize())
        {
            return false;
        }

        m_initialized = true;

        return true;
    }

    void Application::Run()
    {
        if (!m_initialized)
        {
            return;
        }

        // Main application loop (future)
    }
    void Application::Shutdown()
    {
        if (!m_initialized)
        {
            return;
        }

        m_context.Shutdown();

        m_initialized = false;
    }
    const ApplicationContext&
        Application::GetContext() const
    {
        return m_context;
    }
}