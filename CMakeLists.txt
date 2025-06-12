##
## EPITECH PROJECT, 2025
## Zappy-GUI
## File description:
## CMakeLists.txt
##

cmake_minimum_required(VERSION 3.16)
project(zappy_gui VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

########################################
# INFO: enable multithreading for build
########################################
include(ProcessorCount)
ProcessorCount(N)
if(NOT N EQUAL 0)
    set(CMAKE_BUILD_PARALLEL_LEVEL ${N})
endif()

########################################
# INFO: CMake cache management for faster builds
########################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

########################################
# INFO: Raylib graphical library configuration
########################################
add_subdirectory(external/raylib EXCLUDE_FROM_ALL)

########################################
# NOTE: Zappy graphical API
########################################
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c")
add_executable(zappy_gui ${SOURCES})
target_include_directories(zappy_gui PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external
)
target_link_libraries(zappy_gui PRIVATE
    raylib
)
target_compile_options(zappy_gui PRIVATE
    # INFO: classic yutsu warnings
    -Wall
    -Wextra
    -Werror
    -pedantic

    # INFO: type safety & conversions
    -Wconversion
    -Wsign-conversion
    # -Wfloat-equal # << WARN: PURE HATE flag lol

    # INFO: code correctness
    -Wshadow
    -Wnull-dereference
    -Wundef
    -Wuninitialized
    -Winit-self
    -Wredundant-decls

    # INFO: code hygiene
    -Wcast-align
    -Wcast-qual
    -Wmissing-declarations
    # -Woverloaded-virtual << commented because it is not compatible for GCC (only G++)
    # -Wnon-virtual-dtor   << commented because it is not compatible for GCC (only G++)

    # INFO: logic bugs & bad practices
    # -Wduplicated-cond << not on clang
    # -Wduplicated-branches << not on clang
    # -Wlogical-op << not on clang
    -Wswitch-default
    # -Wswitch-enum << commented because i dont think this flag is pertinent (we have default: break...)
    # -Wuseless-cast << not on clang

    # INFO: prevent common portability issues
    -Wdouble-promotion
    -Wformat=2
    -Wwrite-strings
)

option(ENABLE_EXTERNAL "Enable external macros and flags" OFF)
if (ENABLE_EXTERNAL)
    target_compile_definitions(zappy_gui PRIVATE ZAP_DEFAULT_BASE_PATH="external/Zappy-GUI/")
endif()

########################################
# NOTE: debug
########################################
option(ENABLE_DEBUG "Enable debug macros and flags" OFF)

if(ENABLE_DEBUG)
    target_compile_definitions(zappy_gui PRIVATE DEBUG=1)
endif()

