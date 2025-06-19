#!/usr/bin/env bash

GREEN="\033[1;32m"
RED="\033[1;31m"
ILC="\033[3m"
ORG="\033[1;33m"
RST="\033[0m"

function _error()
{
    echo -e "${RED}${BOLD}[❌] ERROR:\n${RST}\t$1\n\t${ILC}\"$2\"${RST}"
    exit 84
}

function _success()
{
    echo -e "${GREEN}[✅] SUCCESS:\t${RST} ${ILC}$1${RST}"
}

function _info()
{
    echo -e "${ORG}[🚧] RUNNING:\t${RST} ${ILC}$1${RST}"
}

set -e

if [[ "$(uname)" == "Darwin" ]]; then
    _info "MacOS found, installing dependencies via Homebrew"

    if ! command -v brew &>/dev/null; then
        _error "Homebrew not found" "Please install Homebrew first: https://brew.sh/"
    fi

    brew update
    brew install \
        libxinerama \
        libxcursor \
        libxrandr \
        libxi \
        libx11 \
        mesa \
        libxext \
        xorg \
        cmake

    exit 0
fi

if [ -f /etc/os-release ]; then
    . /etc/os-release
    DISTRO=$ID_LIKE
else
    _error "Unsupported OS" "Could not determine the distribution from /etc/os-release"
fi

case "$DISTRO" in
    ubuntu|debian)
        _info "Debian-based distribution found, installing dependencies via apt"
        sudo apt-get update
        sudo apt-get install -y \
            libxinerama-dev \
            libxcursor-dev \
            libxrandr-dev \
            libxi-dev \
            libx11-dev \
            libgl1-mesa-dev \
            libxext-dev \
            xorg-dev \
            gcc \
            cmake

        ;;
    alpine)
        _info "Alpine Linux found, installing dependencies via apk"
        sudo apk update
        sudo apk add \
            libxinerama-dev \
            libxcursor-dev \
            libxrandr-dev \
            libxi-dev \
            libx11-dev \
            mesa-dev \
            libxext-dev \
            xorg-server-dev \
            gcc \
            cmake
        ;;
    arch)
        _info "Arch Linux found, installing dependencies via pacman"
        sudo pacman -Syu --noconfirm \
            libxinerama \
            libxcursor \
            libxrandr \
            libxi \
            libx11 \
            mesa \
            libxext \
            xorg-server-devel \
            gcc \
            cmake
        ;;
    *)
        _error "Unsupported distribution" "Please add support for your distribution or use a supported one."
        ;;
esac

if ! cmake --version | grep -q "version 3.25.1"; then
    _info "CMake version is less than 3.25.1, installing CMake 3.25.2"
    wget https://github.com/Kitware/CMake/releases/download/v3.25.2/cmake-3.25.2-linux-x86_64.sh
    chmod +x cmake-3.25.2-linux-x86_64.sh
    sudo ./cmake-3.25.2-linux-x86_64.sh --skip-license --prefix=/usr/local
fi
