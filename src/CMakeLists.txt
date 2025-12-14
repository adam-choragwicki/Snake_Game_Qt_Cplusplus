set(SOURCE_FILES
        game.cpp game.h
        controller.cpp controller.h
        log_manager.cpp log_manager.h
        game_config.cpp game_config.h

        model.h model.cpp

        game_coordinator.cpp game_coordinator.h

        game_loop.cpp game_loop.h
        input_handler.cpp input_handler.h

        arena.cpp arena.h

        snake.h snake.cpp
        head_segment.cpp head_segment.h
        body_segment.h body_segment.cpp
        snake_model.cpp snake_model.h

        coordinates.h coordinates.cpp
        direction.h
        collision_manager.cpp collision_manager.h

        game_config.h game_config.cpp
        window_manager.cpp window_manager.h
        resolution.h
        qml_helper.h
        overlay_manager.cpp overlay_manager.h

        state_machine/game_state_type.h
        state_machine/game_state_manager.h
        state_machine/states/game_ended_state.h

        food_manager.cpp food_manager.h
        food_model.cpp food_model.h
        food_factory.cpp food_factory.h

        score_manager.h
)

add_library(${PROJECT_NAME}Backend ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME}Backend PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME}Backend PUBLIC Qt6::Core Qt6::Quick)

target_compile_definitions(${PROJECT_NAME}Backend PRIVATE
        APP_VERSION="${PROJECT_VERSION}"
        BUILD_TYPE="$<CONFIG>"
)

qt_add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE .)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}Backend SnakeQmlLibplugin)

qt_add_resources(${PROJECT_NAME}
        PREFIX /
        FILES "../assets/resources.qrc"
)

if (WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE $<CONFIG:Release>) # this avoids opening console window on Windows in Release mode
endif ()

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin) # Set the output directory for the executable
