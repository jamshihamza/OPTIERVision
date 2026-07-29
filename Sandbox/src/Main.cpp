#include <optier/Application.h>
#include <optier/FileSystem.h>
#include <iostream>

int main()
{
    auto result =
        optier::FileSystem::ReadTextFile(
            "config/config.json");

    if (!result.IsSuccess())
    {
        return -1;
    }

    std::cout << result.Value() << '\n';
}