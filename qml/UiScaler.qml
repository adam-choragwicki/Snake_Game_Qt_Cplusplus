import QtQuick

Item {
    property bool scalingEnabled: true

    // The root item whose size is used for scaling. This should be set to gameViewport.
    required property Item target

    // Reference resolution for UI layout.
    property int referenceHeight: 880
    property int referenceWidth: 880

    // Scaling factors. UI scale should be based mostly on height for consistency.
    property real scale: target.height / referenceHeight

    // Helpers
    function px(value: real): real {
        if (scalingEnabled) {
            return value * scale
        }

        return value
    }

    function font(value: real): real {
        if (scalingEnabled) {
            return value * scale
        }

        return value
    }
}
