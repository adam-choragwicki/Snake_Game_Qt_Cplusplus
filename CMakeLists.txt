cmake_minimum_required(VERSION 3.10)

project(Snake LANGUAGES CXX)

set(QT_VERSION_MAJOR 6)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets REQUIRED)

set(PROJECT_ROOT ${CMAKE_SOURCE_DIR})
set(BACKEND_DIR ${PROJECT_ROOT}/src/backend)

add_subdirectory(src)
add_subdirectory(tests)
