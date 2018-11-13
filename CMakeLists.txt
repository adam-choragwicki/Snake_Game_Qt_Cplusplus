cmake_minimum_required(VERSION 3.10)

project(Snake LANGUAGES CXX)

set(QT_VERSION_MAJOR 6)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets REQUIRED)

set(PROJECT_ROOT ${CMAKE_SOURCE_DIR})
set(BACKEND_DIR ${PROJECT_ROOT}/src/backend)
set(ASSETS_DIR ${PROJECT_ROOT}/assets)

add_subdirectory(libs/spdlog)

# Enable ccache if available
find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_PROGRAM})
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ${CCACHE_PROGRAM})
endif ()

add_subdirectory(src)
add_subdirectory(tests)
