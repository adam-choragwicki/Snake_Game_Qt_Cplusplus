import QtQuick

Item {
    id: gameInput

    // For keyboard events
    FocusScope {
        id: gameFocusScope
        focus: true

        Keys.onPressed: (event) => {
            Controller.processKeyPress(event.key)
            event.accepted = true
        }

        function refocus() {
            gameFocusScope.forceActiveFocus()
        }
    }

    // Expose helper methods to parent
    function refocus() {
        gameFocusScope.forceActiveFocus()
    }
}
