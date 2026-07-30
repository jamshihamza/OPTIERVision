#pragma once

#include <functional>
#include <vector>

#include <optier/Event.h>

namespace optier
{

    class EventDispatcher
    {
    public:

        using EventCallback =
            std::function<void(const Event&)>;

    public:

        void Subscribe(
            EventCallback callback);

        void Dispatch(
            const Event& event);

    private:

        std::vector<EventCallback> m_subscribers;
    };

}