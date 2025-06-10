/*
** EPITECH PROJECT, 2025
** ZapEngine
** File description:
** Logger.cpp
*/

#include <ZapGUI/Logger.hpp>
#include <iostream>

/**
 * @brief logger::error
 * @details takes an exception::Error and display clearly what is the Error, where was it raised and why
 * @param e the exception::Error to display
 * @return void
 */
void zap::logger::error(const exception::Error &e)
{
    std::cerr << ZAP_RED_BOLD << "╔════════════════════════════════╗" << ZAP_RESET << std::endl
              << ZAP_RED_BOLD << "║       ⚠ ERROR OCCURRED ⚠       ║" << ZAP_RESET << std::endl
              << ZAP_RED_BOLD << "╚════════════════════════════════╝" << ZAP_RESET << std::endl
              << ZAP_YELLOW << "⮞ Raised by: " << ZAP_RESET << e.where() << std::endl
              << ZAP_YELLOW << "⮞ Reason:    " << ZAP_RESET << e.what() << std::endl;
}
