#pragma once

#include <memory>
#include <string>

namespace optier
{

    class JsonDocument
    {
    public:

        JsonDocument();
        ~JsonDocument();

        JsonDocument(const JsonDocument&) = delete;
        JsonDocument& operator=(const JsonDocument&) = delete;

        JsonDocument(JsonDocument&&) noexcept;
        JsonDocument& operator=(JsonDocument&&) noexcept;

        bool Parse(const std::string& text);

        bool Contains(const std::string& key) const;

        std::string GetString(const std::string& key) const;

        int GetInt(const std::string& key) const;

    private:

        class Impl;

        std::unique_ptr<Impl> m_impl;
    };

}