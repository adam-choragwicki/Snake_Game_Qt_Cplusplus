import QtQuick

Item {
    id: gameArea

    onWidthChanged: {
        console.log("Game area width changed to " + width)
    }

    onHeightChanged: {
        console.log("Game area height changed to " + height)
    }

    //
    // ARENA LAYER
    //
    Arena {
        id: arena
        anchors.fill: parent
    }

    //
    // SNAKE LAYER
    //
    Snake {
        snakeSegmentSize: arena.tileSize
    }

    Food {
        foodSize: arena.tileSize
    }

    //
    // INPUT HANDLER
    //
    GameInput {
        id: gameInput
        objectName: "gameInput"
        anchors.fill: parent
    }
}
