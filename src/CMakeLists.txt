set(SOURCE_FILES
        main.cpp
        game.cpp game.h
        controller.cpp controller.h)

add_subdirectory(backend)
add_subdirectory(frontend)

add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${BACKEND_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE lib${PROJECT_NAME}Backend lib${PROJECT_NAME}Frontend)

if (WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_ROOT}/executable_windows)
elseif (UNIX)
    set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_ROOT}/executable_linux)
endif (WIN32)
