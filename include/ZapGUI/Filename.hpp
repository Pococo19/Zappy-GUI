/*
** EPITECH PROJECT, 2025
** Zap-Engine
** File description:
** Filename.hpp
*/

#pragma once

#include <ZapGUI/Error.hpp>

#include <fstream>
#include <vector>

namespace zap::Filename {

[[nodiscard]] std::string getPath(const std::string &name);

[[nodiscard]] bool exists(const std::string &path);

[[nodiscard]] std::string getCurrentDir();

[[nodiscard]] std::vector<std::string> getLines(const std::string &path);

[[nodiscard]] std::string extract(const std::string &path);

template<typename T, typename T_Parser>
[[nodiscard]] T parseFile(const std::string &file_path, T_Parser &&parser, T init_value)
{
    std::ifstream file(file_path);

    if (!file.is_open()) {
        throw zap::exception::Error("Filename::_parse_file", "Could not open file: ", file_path);
    }

    std::string line;

    while (std::getline(file, line)) {
        parser(line, init_value);
    }

    file.close();
    return init_value;
}

}// namespace zap::Filename
