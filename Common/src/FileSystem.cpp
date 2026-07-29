#include "pch.h"

#include <optier/FileSystem.h>

namespace optier
{

    bool FileSystem::Exists(const std::filesystem::path& path)
    {
        return std::filesystem::exists(path);
    }

    bool FileSystem::CreateDirectory(const std::filesystem::path& path)
    {
        return std::filesystem::create_directories(path);
    }

    bool FileSystem::Remove(const std::filesystem::path& path)
    {
        return std::filesystem::remove_all(path) > 0;
    }

}