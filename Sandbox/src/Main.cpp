#include <iostream>

#include <optier/FileSystem.h>
#include <optier/JsonDocument.h>
#include <optier/JsonObject.h>

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

    auto application =
        document.GetObject("Application");

    if (!application.IsValid())
    {
        return -1;
    }

    std::cout
        << application.GetString("Name")
        << '\n';

    return 0;
}