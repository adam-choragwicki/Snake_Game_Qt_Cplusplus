import QtQuick

Window {
    id: mainWindow
    width: Controller.initialRenderResolution.width
    height: Controller.initialRenderResolution.height

    minimumWidth: 500
    minimumHeight: 500
    visible: true
    visibility: Qt.FullScreen

    color: "black"

    Component.onCompleted: {
        if (Controller.startInFullScreenEnabled) {
            mainWindow.showFullScreen()
        } else {
            mainWindow.showNormal()
        }
    }

    property real aspectRatio: width / height

    onAspectRatioChanged: {
        console.log("Window size is now " + width + "x" + height)
        console.log("Aspect ratio is now " + aspectRatio)
    }

    UiScaler {
        id: uiScaler
        target: gameArea   // this ensures UI scales with a visible gameplay area
    }

    /* Maintain the 1:1 aspect ratio with black bars */
    Rectangle {
        id: letterboxContainer
        anchors.fill: parent
        color: "black"

        /* This Item keeps the correct 1:1 scaling inside any window shape */
        Item {
            id: gameViewport
            anchors.centerIn: parent

            property real targetAspect: 1
            property real currentAspect: letterboxContainer.width / letterboxContainer.height

            /* Maintain the 1:1 aspect ratio and center it */
            width: currentAspect > targetAspect ? letterboxContainer.height * targetAspect : letterboxContainer.width
            height: currentAspect > targetAspect ? letterboxContainer.height : letterboxContainer.width / targetAspect

            GameArea {
                id: gameArea
                anchors.fill: parent
            }
        }
    }

    /* Overlays */
    StartingImageOverlay {
        visible: false
    }

    EndGameOverlay {
        visible: false
        objectName: "endGameOverlay"
        anchors.fill: parent
        onPlayAgainClicked: Controller.onPlayAgainClicked()
        onQuitClicked: Controller.onQuitClicked()
    }

    EscapeMenuOverlay {
        visible: false
        objectName: "escapeMenuOverlay"
        anchors.fill: parent

        onResumeClicked: Controller.onResumeClicked()
        onRestartClicked: Controller.onRestartClicked()
        onQuitClicked: Controller.onQuitClicked()
    }
}
