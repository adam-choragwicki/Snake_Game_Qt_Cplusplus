import QtQuick
import CustomEnums

Rectangle {
    id: headRoot

    required property int snakeHeadMovementDirection
    required property real snakeSegmentSize

    color: "yellow"
    radius: snakeSegmentSize * 0.2

    width: snakeSegmentSize
    height: snakeSegmentSize

    // Eye geometry derived from snakeSegmentSize
    readonly property real eyeSocketSize: 0.45 * snakeSegmentSize
    readonly property real halfEyeSocketSize: eyeSocketSize / 2
    readonly property real eyeSocketsSpacing: 0.25 * snakeSegmentSize
    readonly property real pupilSize: 0.20 * snakeSegmentSize

    function computeEyePositions(direction) {
        let eyeXOffset = 0;
        let eyeYOffset = 0;

        if (direction === Direction.LEFT || direction === Direction.RIGHT) {
            eyeXOffset = 0;
            eyeYOffset = eyeSocketsSpacing;
        } else if (direction === Direction.UP || direction === Direction.DOWN) {
            eyeXOffset = eyeSocketsSpacing;
            eyeYOffset = 0;
        } else {
            console.error("HeadSegment: invalid direction:", direction);
        }

        const centerX = snakeSegmentSize / 2.0;
        const centerY = snakeSegmentSize / 2.0;

        const eye1X = centerX + eyeXOffset - halfEyeSocketSize;
        const eye1Y = centerY + eyeYOffset - halfEyeSocketSize;

        const eye2X = centerX - eyeXOffset - halfEyeSocketSize;
        const eye2Y = centerY - eyeYOffset - halfEyeSocketSize;

        return [
            {x: eye1X, y: eye1Y},
            {x: eye2X, y: eye2Y}
        ];
    }

    // pupil geometry
    readonly property real eyeSocketRadiusHalf: eyeSocketSize / 2.0
    readonly property real pupilRadiusHalf: pupilSize / 2.0
    readonly property real pupilMaxOffset: Math.max(0, eyeSocketRadiusHalf - pupilRadiusHalf)

    // HEAD CENTER in snakeLayer coordinates (delegate container positions)
    readonly property real headCenterX: parent.x + parent.width / 2.0
    readonly property real headCenterY: parent.y + parent.height / 2.0

    // FOOD CENTER in snakeLayer coordinates
    readonly property real foodCenterX: foodModel.x * snakeSegmentSize + snakeSegmentSize / 2.0
    readonly property real foodCenterY: foodModel.y * snakeSegmentSize + snakeSegmentSize / 2.0

    // Angle and pupil offsets (in pixels)
    readonly property real angleToFood: Math.atan2(foodCenterY - headCenterY, foodCenterX - headCenterX)
    readonly property real pupilOffsetX: Math.cos(angleToFood) * pupilMaxOffset
    readonly property real pupilOffsetY: Math.sin(angleToFood) * pupilMaxOffset

    // the positions of the two eye sockets in LOCAL coordinates (top-left inside the parent rectangle)
    property var eyesPositionsArray: computeEyePositions(snakeHeadMovementDirection)

    Eye {
        id: eye1
        x: headRoot.eyesPositionsArray[0].x
        y: headRoot.eyesPositionsArray[0].y
        eyeSocketSize: headRoot.eyeSocketSize
        pupilSize: headRoot.pupilSize
        pupilOffsetX: headRoot.pupilOffsetX
        pupilOffsetY: headRoot.pupilOffsetY
    }

    Eye {
        id: eye2
        x: headRoot.eyesPositionsArray[1].x
        y: headRoot.eyesPositionsArray[1].y
        eyeSocketSize: headRoot.eyeSocketSize
        pupilSize: headRoot.pupilSize
        pupilOffsetX: headRoot.pupilOffsetX
        pupilOffsetY: headRoot.pupilOffsetY
    }
}
