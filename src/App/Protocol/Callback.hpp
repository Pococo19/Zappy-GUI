/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Callback.hpp
*/

#pragma once

#include <ZapGUI/NonCopyable.hpp>
#include <ZapGUI/Types.hpp>

#include <functional>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>

namespace zappy::protocol {

class Callback final : public zap::abstract::NonCopyable
{

    public:
        static Callback &getInstance();

        void add(const std::string &cmd, const std::function<void(const std::string &)> &callback);
        bool contains(const std::string &cmd) const;
        void call(const std::string &cmd, const std::string &data) const;
        void clear();

    private:
        std::unordered_map<std::string, std::function<void(const std::string &)>> _commands;
};

template<typename T>
const std::vector<T> parse(const std::string_view line, const u32 expected_count)
{
    std::istringstream iss{std::string(line)};
    std::vector<T> result;
    std::string token;

    result.reserve(expected_count);

    while (iss >> token && result.size() < expected_count) {
        if constexpr (std::is_same_v<T, i32>) {
            result.push_back(static_cast<i32>(std::stoi(token)));
        } else if constexpr (std::is_same_v<T, u32>) {
            result.push_back(static_cast<u32>(std::stoi(token)));
        } else {
            result.push_back(static_cast<T>(token));
        }
    }

    return result;
}

}// namespace zappy::protocol
