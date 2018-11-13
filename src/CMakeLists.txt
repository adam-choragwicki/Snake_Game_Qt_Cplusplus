set(SOURCE_FILES
        main.cpp
        game.cpp game.h
        controller.cpp controller.h)

# Add subdirectories for backend and frontend
add_subdirectory(backend)
add_subdirectory(frontend)

# Create the main executable
add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${BACKEND_DIR})

# Include directories for backend and spdlog
target_include_directories(${PROJECT_NAME} PUBLIC ${BACKEND_DIR} ${PROJECT_ROOT}/libs/spdlog/include)

# Link libraries for backend and frontend
target_link_libraries(${PROJECT_NAME} PRIVATE lib${PROJECT_NAME}Backend lib${PROJECT_NAME}Frontend)

# Set the output directory for the executable
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_ROOT}/bin)
