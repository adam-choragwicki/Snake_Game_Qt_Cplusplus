import QtQuick

Item {
    id: endGameOverlayRoot
    visible: false
    property int currentIndex: 0

    property string message: "NULL" // to be filled from C++ dynamically
    property string score: "NULL" // to be filled from C++ dynamically

    signal playAgainClicked()
    signal quitClicked()

    // Semi-transparent dark layer
    Rectangle {
        anchors.fill: parent
        color: "black"
        opacity: 0.9
    }

    // Centered dialog content
    Column {
        anchors.centerIn: parent
        spacing: uiScaler.px(25)
        width: parent.width * 0.5

        Text {
            text: endGameOverlayRoot.message
            color: "white"
            font.pixelSize: uiScaler.font(64)
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            text: "SCORE\n" + endGameOverlayRoot.score
            color: "white"
            font.pixelSize: uiScaler.font(40)
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Repeater {
            model: ["PLAY AGAIN", "QUIT"]

            delegate: Rectangle {
                width: uiScaler.px(400)
                height: uiScaler.px(100)
                radius: uiScaler.px(16)
                anchors.horizontalCenter: parent.horizontalCenter

                color: index === endGameOverlayRoot.currentIndex ? "#3A3A3A" : "#2A2A2A"
                border.color: index === endGameOverlayRoot.currentIndex ? "#5BC0EB": "#00000000"
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
                    onEntered: endGameOverlayRoot.currentIndex = index
                    onClicked: {
                        if (index === 0) endGameOverlayRoot.playAgainClicked()
                        else endGameOverlayRoot.quitClicked()
                    }
                }
            }
        }
    }
}
