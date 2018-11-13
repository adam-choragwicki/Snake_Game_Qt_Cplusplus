set(TEST_SOURCES
        src/main.cpp
        src/common_test_fixture.h
        src/config_test.h
        src/snake_creation_test.cpp
        src/snake_movement_test.cpp
        src/snake_growth_test.cpp
        src/snake_collision_with_itself_test.cpp
        src/snake_collision_with_wall_test.cpp)

add_subdirectory(googletest)

# Create the test executable
add_executable(${PROJECT_NAME}Test_run ${TEST_SOURCES})

# Link to the backend library and test libraries
target_link_libraries(${PROJECT_NAME}Test_run PRIVATE gtest lib${PROJECT_NAME}Backend Qt${QT_VERSION_MAJOR}::Widgets)

target_include_directories(${PROJECT_NAME}Test_run PRIVATE src)
