cmake_minimum_required(VERSION 3.10)

project(SnakeTest LANGUAGES CXX)

set(TEST_SOURCES
    src/main.cpp
    src/common_test_fixture.cpp
    src/snake_test.cpp)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(SnakeTest_run ${TEST_SOURCES})
target_include_directories(SnakeTest_run PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries(SnakeTest_run gtest gtest_main libSnake)
