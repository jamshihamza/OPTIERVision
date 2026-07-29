#include "pch.h"

#include <optier/JsonDocument.h>

#include <nlohmann/json.hpp>

#include <utility>

namespace optier
{

    //=========================================================
    // Private Implementation
    //=========================================================

    class JsonDocument::Impl
    {
    public:

        nlohmann::json Document;
    };

    //=========================================================
    // Constructors / Destructor
    //=========================================================

    JsonDocument::JsonDocument()
        : m_impl(std::make_unique<Impl>())
    {
    }

    JsonDocument::~JsonDocument() = default;

    JsonDocument::JsonDocument(JsonDocument&&) noexcept = default;

    JsonDocument& JsonDocument::operator=(JsonDocument&&) noexcept = default;

    //=========================================================
    // Public API
    //=========================================================

    bool JsonDocument::Parse(const std::string& text)
    {
        try
        {
            m_impl->Document = nlohmann::json::parse(text);
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    bool JsonDocument::Contains(const std::string& key) const
    {
        return m_impl->Document.contains(key);
    }

    std::string JsonDocument::GetString(const std::string& key) const
    {
        return m_impl->Document.at(key).get<std::string>();
    }

    int JsonDocument::GetInt(const std::string& key) const
    {
        return m_impl->Document.at(key).get<int>();
    }

}