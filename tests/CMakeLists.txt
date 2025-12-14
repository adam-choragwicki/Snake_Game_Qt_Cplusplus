cmake_minimum_required(VERSION 3.16)

set(GOOGLETEST_VERSION 1.17.0)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(googletest)

set(TEST_SOURCES
        src/main.cpp
        src/common_test_fixture.h
        src/config_test.h
        src/snake_creation_test.cpp
        src/snake_movement_test.cpp
        src/snake_growth_test.cpp
        src/snake_collision_with_itself_test.cpp
        src/snake_collision_with_wall_test.cpp)

# Create the test executable
add_executable(${PROJECT_NAME}Test_run ${TEST_SOURCES})

# Link to the backend library and test libraries
target_link_libraries(${PROJECT_NAME}Test_run PRIVATE gtest SnakeCore Qt6::Widgets)

target_include_directories(${PROJECT_NAME}Test_run PRIVATE src)

# Enable CTest
enable_testing()
add_test(NAME AllTests COMMAND runTests)
