/*
** EPITECH PROJECT, 2025
** Zappy-GUI
** File description:
** Arguments.cpp
*/

#include <App/Arguments.hpp>
#include <ZapGUI/Error.hpp>

#include <iostream>

void parser::usage()
{
    std::cout << "Usage: zappy-gui [options]" << std::endl
              << "Options:" << std::endl
              << "  -p <port>       Set the port number (default: 0)" << std::endl
              << "  -h <hostname>   Set the hostname (default: localhost)" << std::endl
              << "  -v, --version   Show version information" << std::endl
              << "  -help, --help      Show this help message" << std::endl;
}

void parser::version()
{
    std::cout << "Zappy GUI Version " << ZAP_GUI_VERSION << std::endl;
}

/**
* @brief parser::parse
* @details parse flags see --help for usage
* @return Flags (struct defined in Parse.hpp)
*/
const parser::Flags parser::parse(const int argc, const char **argv)
{
    parser::Flags flags;

    /**
     * @brief zap client execution flags
     * @details parse and check all flags are valid using lambda
     */
    static const std::unordered_map<std::string, std::function<void(int &)>> _jp_flags = {
        /**
        * @brief -h
        * @details define the remote server IP
        */
        {"-h",
            [&](int &i) {
                if (++i >= argc) {
                    throw zap::exception::Error("parser::parse", "Missing value after -h");
                }
                if (!flags.hostname.empty()) {
                    throw zap::exception::Error("parser::parse", "IP already set");
                }
                const std::string ip = argv[i];

                if (!std::regex_match(ip, ipv4_regex)) {
                    throw zap::exception::Error("parser::parse", "Invalid IP address format: ", ip);
                }
                flags.hostname = ip;
            }},

        /**
        * @brief -p
        * @details define the port to connect
        */
        {"-p",
            [&](int &i) {
                if (++i >= argc) {
                    throw zap::exception::Error("parser::parse", "Missing value after -p");
                }
                if (flags.port != PORT_MIN) {
                    throw zap::exception::Error("parser::parse", "Port already set");
                }

                try {
                    const int port = std::stoi(argv[i]);
                    if (port <= PORT_MIN || port > PORT_MAX) {
                        throw zap::exception::Error("parser::parse", "Port out of range (1-65535)");
                    }
                    flags.port = static_cast<u16>(port);
                } catch (const std::invalid_argument &) {
                    throw zap::exception::Error("parser::parse", "Invalid port: must be a number");
                } catch (const std::out_of_range &) {
                    throw zap::exception::Error("parser::parse", "Port value is too large");
                }
            }},
    };

    /**
     * @brief main parser loop
     * @details iterate in arguments and ensure they are valid
     */
    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];

        if (__meta_flags.contains(arg)) {
            __meta_flags.at(arg)();

        } else if (_jp_flags.contains(arg)) {

            _jp_flags.at(arg)(i);

        } else {
            throw zap::exception::Error("parser::parse", "Unknown option: ", arg);
        }
    }

    if (flags.hostname.empty() || flags.port == 0) {
        throw zap::exception::Error("parser::parse", "Missing required flags: -h <ip> and -p <port>");
    }

    return flags;
}
