import QtQuick

Item {
    id: food
    required property real foodSize

    width: foodSize
    height: foodSize

    x: foodModel.x * foodSize
    y: foodModel.y * foodSize

    // scale from a center
    transformOrigin: Item.Center

    // base scale
    scale: 1.0

    // Body
    Rectangle {
        id: body
        anchors.fill: parent
        radius: width / 2
        color: "#d63c2f"
    }

    // Stem
    Rectangle {
        width: parent.width * 0.08
        height: parent.height * 0.25
        radius: width / 2
        color: "#5a3a1a"
        anchors.horizontalCenter: parent.horizontalCenter
        y: -height * 0.3
    }

    // Leaf
    Rectangle {
        width: parent.width * 0.3
        height: parent.height * 0.15
        radius: height / 2
        color: "#3fa34d"
        anchors.left: parent.horizontalCenter
        anchors.top: parent.top
        rotation: -25
        y: parent.height * 0.05
    }

    // Highlight (gives depth)
    Rectangle {
        width: parent.width * 0.35
        height: parent.height * 0.35
        radius: width / 2
        color: "#fabebe"
        x: parent.width * 0.18
        y: parent.height * 0.15
    }

    SequentialAnimation on scale {
        loops: Animation.Infinite

        NumberAnimation {
            from: 1.0
            to: 0.85
            duration: 450
            easing.type: Easing.InOutQuad
        }

        NumberAnimation {
            from: 0.85
            to: 1.0
            duration: 450
            easing.type: Easing.InOutQuad
        }
    }
}
