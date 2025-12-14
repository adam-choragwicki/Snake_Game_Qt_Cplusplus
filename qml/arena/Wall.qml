import QtQuick

Rectangle {
    id: wall

    required property real tileSize

    readonly property color brickColor: "#7b2d1f"
    readonly property real mortar: tileSize * 0.08
    readonly property color mortarColor: "#2a120d"

    // wall colors
    border.color: "#00000055"
    border.width: 1

    color: brickColor

    Rectangle {
        width: parent.width
        height: mortar
        y: parent.height / 2 - height / 2
        color: mortarColor
    }

    Rectangle {
        width: mortar
        height: parent.height / 2
        x: (gridY % 2 === 0) ? parent.width * 0.33 : parent.width * 0.66
        y: 0
        color: mortarColor
    }

    Rectangle {
        width: mortar
        height: parent.height / 2
        x: (gridY % 2 === 0) ? parent.width * 0.66 : parent.width * 0.33
        y: parent.height / 2
        color: mortarColor
    }
}
