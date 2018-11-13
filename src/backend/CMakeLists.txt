set(SOURCE_FILES
        model/model.h model/model.cpp

        game_loop.cpp game_loop.h
        input_handler.cpp input_handler.h
        game_manager.cpp game_manager.cpp

        model/graphics_scene.cpp model/graphics_scene.h

        model/arena.cpp model/arena.h

        model/custom_graphics_item.cpp model/custom_graphics_item.cpp
        model/tiles/wall.cpp model/tiles/wall.h
        model/food.h model/food.cpp
        model/snake.h model/snake.cpp
        model/head_segment.cpp model/head_segment.h
        model/body_segment.h model/body_segment.cpp
        model/food_factory.cpp model/food_factory.h
        model/food_manager.cpp model/food_manager.h
        coordinates.h coordinates.cpp
        direction.h
        config_prod.cpp config_prod.h
        collision_manager.cpp collision_manager.h
        snake_reverse_iterator.cpp snake_reverse_iterator.h
        animation_manager.cpp animation_manager.h
        model/tiles/background_tiles/abstract_background_tile.cpp model/tiles/background_tiles/abstract_background_tile.h
        model/tiles/background_tiles/background_tile.cpp model/tiles/background_tiles/background_tile.h)

# Create the backend library
add_library(lib${PROJECT_NAME}Backend ${SOURCE_FILES})

# Include current directory for backend library
target_include_directories(lib${PROJECT_NAME}Backend PUBLIC .)

# Link Qt Core library to backend
target_link_libraries(lib${PROJECT_NAME}Backend PUBLIC spdlog::spdlog Qt${QT_VERSION_MAJOR}::Gui)
