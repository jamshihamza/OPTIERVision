#include "pch.h"

#include <optier/JsonObject.h>

namespace optier
{

    JsonObject::JsonObject()
        : m_object(nullptr)
    {
    }

    JsonObject::JsonObject(
        const nlohmann::json* object)
        : m_object(object)
    {
    }

    bool JsonObject::IsValid() const
    {
        return m_object != nullptr;
    }

    bool JsonObject::Contains(
        const std::string& key) const
    {
        if (!IsValid())
        {
            return false;
        }

        return m_object->contains(key);
    }

    JsonObject JsonObject::GetObject(
        const std::string& key) const
    {
        if (!Contains(key))
        {
            return JsonObject();
        }

        const auto& value = m_object->at(key);

        if (!value.is_object())
        {
            return JsonObject();
        }

        return JsonObject(&value);
    }

    std::string JsonObject::GetString(
        const std::string& key) const
    {
        if (!Contains(key))
        {
            return {};
        }

        return m_object->at(key).get<std::string>();
    }

    int JsonObject::GetInt(
        const std::string& key) const
    {
        if (!Contains(key))
        {
            return 0;
        }

        return m_object->at(key).get<int>();
    }

    bool JsonObject::GetBool(
        const std::string& key) const
    {
        if (!Contains(key))
        {
            return false;
        }

        return m_object->at(key).get<bool>();
    }

    double JsonObject::GetDouble(
        const std::string& key) const
    {
        if (!Contains(key))
        {
            return 0.0;
        }

        return m_object->at(key).get<double>();
    }

}