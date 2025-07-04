/*
** EPITECH PROJECT, 2025
** ZapGUI-Engine
** File description:
** Filename.cpp
*/

#include <ZapGUI/Filename.hpp>

#include <filesystem>

std::string zap::Filename::getPath(const std::string &name)
{
    const std::filesystem::path absolute = std::filesystem::absolute(ZAP_DEFAULT_BASE_PATH + name);

    return absolute.string();
}

bool zap::Filename::exists(const std::string &path)
{
    return std::filesystem::exists(path);
}

std::string zap::Filename::getCurrentDir()
{
    return std::filesystem::current_path().string();
}

std::vector<std::string> zap::Filename::getLines(const std::string &path)
{
    if (!exists(path)) {
        throw exception::Error("zap::Filename::getLines", "file: ", path, " does not exist!");
    }

    std::ifstream file(path);

    if (!file.is_open()) {
        throw exception::Error("zap::Filename::getLines", "cannot open file: ", path);
    }

    std::vector<std::string> lines;
    std::string line;

    while (std::getline(file, line)) {
        lines.push_back(std::move(line));
    }

    return lines;
}

std::string zap::Filename::extract(const std::string &path)
{
    const size_t last_slash = path.find_last_of("/\\");

    if (last_slash == std::string::npos) {
        return path;
    }
    return path.substr(last_slash + 1);
}
