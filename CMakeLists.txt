cmake_minimum_required(VERSION 3.10)

project(Snake VERSION 2.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.9.2 COMPONENTS Core Quick QuickControls2Basic QuickLayouts REQUIRED)

qt_standard_project_setup(REQUIRES 6.9)

# Enable ccache if available
find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_PROGRAM})
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ${CCACHE_PROGRAM})
endif ()

add_subdirectory(src)
add_subdirectory(qml)
add_subdirectory(tests)
