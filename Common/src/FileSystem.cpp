#include "pch.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>

#include <optier/FileSystem.h>

namespace optier
{

    bool FileSystem::Exists(const std::filesystem::path& path)
    {
        auto current = std::filesystem::current_path();
        bool exists = std::filesystem::exists(path);

        std::cout << "Current Path : " << current << '\n';
        std::cout << "Looking For  : " << path << '\n';
        std::cout << "Exists       : " << std::boolalpha << exists << '\n';

        return exists;
    }

    bool FileSystem::CreateDirectory(const std::filesystem::path& path)
    {
        return std::filesystem::create_directories(path);
    }

    bool FileSystem::Remove(const std::filesystem::path& path)
    {
        return std::filesystem::remove_all(path) > 0;
    }

    Result<std::string> FileSystem::ReadTextFile(
        const std::filesystem::path& path)
    {
        std::ifstream file(path);

        if (!file.is_open())
        {
            return Result<std::string>::Failure(
                ErrorCode::FileNotFound);
        }

        std::stringstream buffer;

        buffer << file.rdbuf();

        return Result<std::string>::Success(
            buffer.str());
    }

}