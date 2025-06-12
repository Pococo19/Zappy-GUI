/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Arguments.hpp
*/

#pragma once

#include <ZapGUI/Macro.hpp>
#include <ZapGUI/Types.hpp>

#include <functional>
#include <regex>
#include <string>
#include <unordered_map>

namespace parser {

static constexpr int PORT_MIN = 0;
static constexpr int PORT_MAX = 65535;

struct Flags {
        u16 port = 0;
        std::string hostname;
};

void usage();
void version();

[[nodiscard]] const Flags parse(const int argc, const char **argv);

static const std::unordered_map<std::string, std::function<void()>> __meta_flags = {
    {"-help",
        []() {
            usage();
            std::exit(SUCCESS);
        }},
    {"--help",
        []() {
            usage();
            std::exit(SUCCESS);
        }},
    {"-v",
        []() {
            version();
            std::exit(SUCCESS);
        }},
    {"--version",
        []() {
            version();
            std::exit(SUCCESS);
        }},
};

static const std::regex ipv4_regex(R"(^(25[0-5]|2[0-4][0-9]|1?[0-9]{1,2})(\.(25[0-5]|2[0-4][0-9]|1?[0-9]{1,2})){3}$)");

}// namespace parser
