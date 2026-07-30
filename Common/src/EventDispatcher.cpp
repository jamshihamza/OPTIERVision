#include "pch.h"

#include <optier/EventDispatcher.h>
#include <optier/Logger.h>

namespace optier
{

    void EventDispatcher::Subscribe(
        EventCallback callback)
    {
        m_subscribers.push_back(
            std::move(callback));
    }

    void EventDispatcher::Dispatch(
        const Event& event)
    {
        Logger::Info(
            "Dispatching Event : " + event.GetName());

        for (const auto& callback : m_subscribers)
        {
            callback(event);
        }
    }

}