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

function _base_run()
{
    local cmake_args="$1"

    if ! { command -v cmake > /dev/null; } 2>&1; then
        _error "command 'cmake' not found" "please install 'cmake' or 'nix develop' 🤓"
    fi
    _success "command 'cmake' found, building..."
    _info "updating external submodules..."
    git submodule update --init --recursive
    _success "updated external submodules !"
    mkdir -p build
    cd build || _error "mkdir failed"
    cmake .. -G "Unix Makefiles" $cmake_args
    if ! make -j"$(nproc)" zappy_gui; then
        _error "compilation error" "failed to compile zappy_gui"
    fi
    _success "compiled zappy_gui"
}

function _all()
{
    _base_run "-DCMAKE_BUILD_TYPE=Release -DENABLE_DEBUG=OFF -DENABLE_EXTERNAL=OFF"
    exit 0
}

function _external()
{
    _base_run "-DCMAKE_BUILD_TYPE=Release -DENABLE_DEBUG=OFF -DENABLE_EXTERNAL=ON"
    exit 0
}

function _debug()
{
    _base_run "-DCMAKE_BUILD_TYPE=Debug -DENABLE_DEBUG=ON -DENABLE_EXTERNAL=OFF"
    exit 0
}

function _tests_run()
{
    _base_run "-DCMAKE_BUILD_TYPE=Debug -DENABLE_EXTERNAL=OFF -DENABLE_DEBUG=ON"
    cd .. || _error "cd failed"
    if ! ./unit_tests; then
        _error "unit tests error" "unit tests failed!"
    fi
    _success "unit tests succeed!"
    if [ "$(uname -s)" == 'Darwin' ]; then
        xcrun llvm-profdata merge -sparse unit_tests-*.profraw -o unit_tests.profdata
        xcrun llvm-cov report ./unit_tests -instr-profile=unit_tests.profdata -ignore-filename-regex='.*/tests/.*' -enable-name-compression > code_coverage.txt
    else
        gcovr -r . --exclude tests/ > code_coverage.txt
    fi
    cat code_coverage.txt
    exit 0
}

function _clean()
{
    rm -rf build
    exit 0
}

function _fclean()
{
    _clean
    rm -rf zappy_gui unit_tests plugins code_coverage.txt unit_tests-*.profraw unit_tests.profdata vgcore* cmake-build-debug
    exit 0
}

for args in "$@"
do
    case $args in
        -h|--help)
            cat << EOF
USAGE:
      $0    builds zappy_gui project

ARGUMENTS:
      $0 [-h|--help]    displays this message
      $0 [-d|--debug]   debug flags compilation
      $0 [-c|--clean]   clean the project
      $0 [-f|--fclean]  fclean the project
      $0 [-t|--tests]   run unit tests
EOF
        exit 0
        ;;
    -e|--external)
        _external
        ;;
    -c|--clean)
        _clean
        ;;
    -f|--fclean)
        _fclean
        ;;
    -d|--debug)
        _debug
        ;;
    -t|--tests)
        _tests_run
        ;;
    -r|--re)
        _fclean
        _all
        ;;
    *)
        _error "Invalid arguments: " "$args"
    esac
done

_all
