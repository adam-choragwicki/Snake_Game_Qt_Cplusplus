cmake_minimum_required(VERSION 3.10)

project(Snake LANGUAGES CXX)

set(QT_VERSION_MAJOR 6)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(PROJECT_ROOT ${CMAKE_SOURCE_DIR})

set(INCLUDES_DIR ${PROJECT_ROOT}/inc)
set(SOURCES_DIR ${PROJECT_ROOT}/src)
set(UI_FORMS_DIR ${PROJECT_ROOT}/ui_forms)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${UI_FORMS_DIR})

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(SOURCE_FILES
    ${SOURCES_DIR}/main.cpp
    ${INCLUDES_DIR}/common.h
    ${INCLUDES_DIR}/game_window.h ${SOURCES_DIR}/game_window.cpp ${UI_FORMS_DIR}/game_window.ui
    ${INCLUDES_DIR}/food.h ${SOURCES_DIR}/food.cpp
    ${INCLUDES_DIR}/snake.h ${SOURCES_DIR}/snake.cpp
    ${INCLUDES_DIR}/drawer.h ${SOURCES_DIR}/drawer.cpp)

add_library(libSnake ${SOURCE_FILES})
target_include_directories(libSnake PUBLIC ${INCLUDES_DIR})
target_link_libraries(libSnake Qt${QT_VERSION_MAJOR}::Widgets)

add_executable(Snake WIN32 ${SOURCES_DIR}/main.cpp)
target_link_libraries(Snake PRIVATE libSnake)

if(WIN32)
    set_target_properties(Snake PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_ROOT}/executable_windows)
elseif(UNIX)
    set_target_properties(Snake PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_ROOT}/executable_linux)
endif()

add_subdirectory(tests)
