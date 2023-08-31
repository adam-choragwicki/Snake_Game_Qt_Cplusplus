set(TEST_SOURCES
        src/main.cpp
        src/snake_creation_test.cpp
        src/snake_movement_test.cpp
        src/snake_growth_test.cpp
        src/snake_collision_with_itself_test.cpp
        src/snake_collision_with_wall_test.cpp)

add_subdirectory(googletest)

add_executable(${PROJECT_NAME}Test_run ${TEST_SOURCES})
target_include_directories(${PROJECT_NAME}Test_run PRIVATE src)
target_link_libraries(${PROJECT_NAME}Test_run PRIVATE gtest lib${PROJECT_NAME}Backend)
