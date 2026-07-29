#pragma once

#include <filesystem>

namespace optier
{

    class FileSystem
    {
    public:

        static bool Exists(const std::filesystem::path& path);

        static bool CreateDirectory(const std::filesystem::path& path);

        static bool Remove(const std::filesystem::path& path);
    };

}