set(MODULE_NAME SnakeQml)
set(LIB_NAME ${MODULE_NAME}Lib) # SnakeQmlLib

qt_add_library(${LIB_NAME} STATIC)

target_link_libraries(${LIB_NAME} PRIVATE Qt6::Quick)

qt_add_qml_module(${LIB_NAME}
        URI ${MODULE_NAME}
        VERSION 1.0
        OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/SnakeQml
        QML_FILES
        Main.qml
        GameArea.qml
        GameInput.qml
        UiScaler.qml
        Food.qml

        arena/Arena.qml
        arena/Wall.qml

        snake/Snake.qml
        snake/HeadSegment.qml
        snake/BodySegment.qml
        snake/Eye.qml

        overlays/StartingImageOverlay.qml
        overlays/EndGameOverlay.qml
        overlays/EscapeMenuOverlay.qml
)
