#include <iostream>
#include <nlohmann/json.hpp>
#include <optier/FileSystem.h>
#include <optier/JsonDocument.h>

int main()
{
    auto file =
        optier::FileSystem::ReadTextFile(
            "config/config.json");

    if (!file.IsSuccess())
    {
        return -1;
    }

    optier::JsonDocument document;

    if (!document.Parse(file.Value()))
    {
        return -1;
    }

    std::cout
        << document.GetString("Application")
        << '\n';
}