set(SOURCE_FILES
        model/model.h model/model.cpp
        model/food.h model/food.cpp
        model/snake.h model/snake.cpp
        model/game_speed_manager.h model/game_speed_manager.cpp
        model/snake_segment.h model/snake_segment.cpp
        model/food_factory.cpp model/food_factory.h
        model/game_state_manager.cpp model/game_state_manager.h
        model/food_manager.cpp model/food_manager.h
        coordinates.h coordinates.cpp
        direction.h
        config.h
        log_manager.h
        collision_detector.cpp collision_detector.h
        speed_level.cpp speed_level.h
        game_parameters.h
        snake_iterator.cpp snake_iterator.h)

add_library(lib${PROJECT_NAME}Backend ${SOURCE_FILES})
target_include_directories(lib${PROJECT_NAME}Backend PUBLIC .)
target_link_libraries(lib${PROJECT_NAME}Backend PUBLIC Qt${QT_VERSION_MAJOR}::Core)
