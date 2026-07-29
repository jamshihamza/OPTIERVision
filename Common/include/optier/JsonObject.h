#pragma once

#include <string>

#include <nlohmann/json.hpp>

namespace optier
{

    class JsonObject
    {
    public:

        JsonObject();

        explicit JsonObject(
            const nlohmann::json* object);

        bool IsValid() const;

        bool Contains(
            const std::string& key) const;

        JsonObject GetObject(
            const std::string& key) const;

        std::string GetString(
            const std::string& key) const;

        int GetInt(
            const std::string& key) const;

        bool GetBool(
            const std::string& key) const;

        double GetDouble(
            const std::string& key) const;

    private:

        const nlohmann::json* m_object;
    };

}