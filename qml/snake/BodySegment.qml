import QtQuick

Rectangle {
    id: bodyRoot

    required property real snakeSegmentSize

    width: snakeSegmentSize
    height: snakeSegmentSize

    color: "#4674E9"
    radius: snakeSegmentSize * 0.2
}
