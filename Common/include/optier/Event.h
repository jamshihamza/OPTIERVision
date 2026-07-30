#pragma once

#include <string>

namespace optier
{

    class Event
    {
    public:

        virtual ~Event() = default;

        virtual std::string GetName() const = 0;
    };

}
