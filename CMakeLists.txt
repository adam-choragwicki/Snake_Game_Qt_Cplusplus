cmake_minimum_required(VERSION 3.10)

project(Snake LANGUAGES CXX)

add_definitions(-DAPP_VERSION="2.0.0")
add_definitions(-DBUILD_TYPE="${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.9.2 COMPONENTS Core Widgets Quick REQUIRED)

qt_standard_project_setup(REQUIRES 6.9)

set(PROJECT_ROOT ${CMAKE_SOURCE_DIR})

set(ASSETS_DIR ${PROJECT_ROOT}/assets)

# Enable ccache if available
find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_PROGRAM})
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ${CCACHE_PROGRAM})
endif ()

add_subdirectory(src)
add_subdirectory(qml)
add_subdirectory(tests)
