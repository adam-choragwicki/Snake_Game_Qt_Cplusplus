import QtQuick

Item {
    id: startingImageOverlay
    objectName: "startingImageOverlay" // Required for C++ lookup

    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter

    // shift upward by a scaled amount
    anchors.verticalCenterOffset: - uiScaler.px(200)

    Image{
        anchors.centerIn: parent
        width: uiScaler.px(300)
        height: uiScaler.px(300)

        smooth: true
        source: "qrc:/images/arrow_keys.png"
    }
}
