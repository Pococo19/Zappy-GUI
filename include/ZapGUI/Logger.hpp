/*
** EPITECH PROJECT, 2025
** ZapEngine
** File description:
** Logger.hpp
*/

#pragma once

#include <ZapGUI/Error.hpp>

#ifdef DEBUG
    #include <iostream>
    #include <sstream>
#endif

namespace zap::logger {

constexpr const char *ZAP_GRAY = "\033[38;5;8m";
constexpr const char *ZAP_RED_BOLD = "\033[1;31m";
constexpr const char *ZAP_YELLOW = "\033[1;33m";
constexpr const char *ZAP_GREEN = "\033[1;32m";
constexpr const char *ZAP_BLUE = "\033[1;34m";
constexpr const char *ZAP_RESET = "\033[0m";

void error(const zap::exception::Error &e);

template<typename... Args>
static inline void debug(__attribute_maybe_unused__ Args &&...args)
{
#ifdef DEBUG
    std::ostringstream oss;
    int __attribute__((unused)) _[] = {0, (oss << args, 0)...};
    std::cout << ZAP_BLUE << "[DEBUG] " << ZAP_RESET << oss.str() << std::endl;
#endif
}

template<typename... Args>
static inline void task_start(__attribute_maybe_unused__ Args &&...args)
{
#ifdef DEBUG
    std::ostringstream oss;
    int __attribute__((unused)) _[] = {0, (oss << args, 0)...};
    std::cout << ZAP_YELLOW << "[TASK START] " << ZAP_RESET << oss.str() << std::endl;
#endif
}

template<typename... Args>
static inline void task_done(__attribute_maybe_unused__ Args &&...args)
{
#ifdef DEBUG
    std::ostringstream oss;
    int __attribute__((unused)) _[] = {0, (oss << args, 0)...};
    std::cout << ZAP_GREEN << "[TASK DONE] " << ZAP_RESET << oss.str() << std::endl;
#endif
}

}// namespace zap::logger
