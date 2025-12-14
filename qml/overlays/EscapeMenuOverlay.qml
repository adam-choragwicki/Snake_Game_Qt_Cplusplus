import QtQuick

Item {
    id: escapeMenuOverlayRoot
    visible: false
    property int currentIndex: 0

    signal resumeClicked()
    signal restartClicked()
    signal quitClicked()

    // Semi-transparent dark layer
    Rectangle {
        anchors.fill: parent
        color: "black"
        opacity: 0.9
    }

    Column {
        anchors.centerIn: parent
        spacing: uiScaler.px(40)

        Repeater {
            model: ["RESUME", "RESTART", "QUIT"]

            delegate: Rectangle {
                width: uiScaler.px(400)
                height: uiScaler.px(100)
                radius: uiScaler.px(16)

                color: index === escapeMenuOverlayRoot.currentIndex ? "#3A3A3A" : "#2A2A2A"
                border.color: index === escapeMenuOverlayRoot.currentIndex ? "#5BC0EB": "#00000000"
                border.width: uiScaler.px(10)

                Text {
                    anchors.centerIn: parent
                    text: modelData
                    color: "white"
                    font.pixelSize: uiScaler.font(36)
                    font.bold: true
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: escapeMenuOverlayRoot.currentIndex = index
                    onClicked: {
                        if (index === 0) escapeMenuOverlayRoot.resumeClicked()
                        else if (index === 1) escapeMenuOverlayRoot.restartClicked()
                        else escapeMenuOverlayRoot.quitClicked()
                    }
                }
            }
        }
    }
}
