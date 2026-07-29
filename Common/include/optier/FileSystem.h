#pragma once

#include <filesystem>
#include <string>
#include <optier/Result.h>
namespace optier
{

    class FileSystem
    {
    public:

        static bool Exists(const std::filesystem::path& path);

        static bool CreateDirectory(const std::filesystem::path& path);

        static bool Remove(const std::filesystem::path& path);

        static Result<std::string> ReadTextFile(const std::filesystem::path& path);
    };

}