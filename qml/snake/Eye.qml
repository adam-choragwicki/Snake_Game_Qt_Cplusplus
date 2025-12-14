import QtQuick

Rectangle {
    id: eyeRoot

    required property real eyeSocketSize
    required property real pupilSize
    required property real pupilOffsetX
    required property real pupilOffsetY

    width: eyeSocketSize
    height: eyeSocketSize
    radius: width / 2
    color: "white"

    Rectangle {
        id: pupil
        width: eyeRoot.pupilSize
        height: eyeRoot.pupilSize
        radius: width / 2
        color: "black"
        anchors.centerIn: parent

        transform: Translate { x: eyeRoot.pupilOffsetX; y: eyeRoot.pupilOffsetY }
    }
}
