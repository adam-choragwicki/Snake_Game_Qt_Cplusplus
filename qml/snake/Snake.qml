import QtQuick

Item {
    id: snakeLayer
    objectName: "snakeLayer"

    property bool snakeAnimationsEnabled: false

    property int animMs: snakeMovementIntervalMs // (from C++ context property)

    required property real snakeSegmentSize

    // Draw each segment of the snake
    Instantiator {
        model: snakeModel

        delegate: Item {
            parent: snakeLayer

            width: snakeLayer.snakeSegmentSize
            height: snakeLayer.snakeSegmentSize

            // convert logical coordinates to scaled coordinates
            x: positionXRole * snakeLayer.snakeSegmentSize
            y: positionYRole * snakeLayer.snakeSegmentSize

            // Animate movement smoothly
            Behavior on x {
                enabled: snakeLayer.snakeAnimationsEnabled

                NumberAnimation {
                    duration: animMs;
                    easing.type: Easing.Linear
                }
            }

            Behavior on y {
                enabled: snakeLayer.snakeAnimationsEnabled

                NumberAnimation {
                    duration: animMs;
                    easing.type: Easing.Linear
                }
            }

            HeadSegment {
                anchors.fill: parent
                visible: index === 0
                snakeHeadMovementDirection: snakeHeadMovementDirectionRole
                snakeSegmentSize: snakeLayer.snakeSegmentSize
            }

            BodySegment {
                anchors.fill: parent
                visible: index !== 0
                snakeSegmentSize: snakeLayer.snakeSegmentSize
            }
        }
    }
}
