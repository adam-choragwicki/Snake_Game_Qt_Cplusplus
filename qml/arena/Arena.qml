import QtQuick

Item {
    id: arenaRoot

    onWidthChanged: {
        console.log("Arena width changed to " + width)
    }

    onHeightChanged: {
        console.log("Arena height changed to " + height)
    }

    // Colors used in an arena
    readonly property color backgroundTileColor1: Qt.rgba(170 / 255, 215 / 255, 81 / 255, 1) // light green
    readonly property color backgroundTileColor2: Qt.rgba(162 / 255, 209 / 255, 73 / 255, 1) // slightly darker green

    property real tileSize: width / gridColumnCount // Actual aspect ratio is 1:1 so width/height does not matter here

    readonly property int gridRowCount: totalRowCountIncludingBoundaryWalls  // (from C++ context property)
    readonly property int gridColumnCount: totalColumnCountIncludingBoundaryWalls // (from C++ context property)

    // BACKGROUND TILES (checkerboard pattern)
    Repeater {
        model: gridRowCount * gridColumnCount // total number of squares in the grid

        delegate: Rectangle {
            width: tileSize
            height: tileSize

            // Compute the coordinates in the grid
            // gridX: column index (0 to gridColumnCount-1)
            // gridY: row index (0 to gridRowCount-1)
            property int gridX: index % gridColumnCount
            property int gridY: Math.floor(index / gridColumnCount)

            // Place the tile at its position
            x: gridX * tileSize
            y: gridY * tileSize

            // Checkerboard coloring, alternate colors to create the classic snake background pattern
            color: {
                if (gridX % 2 === 0) {
                    return (gridY % 2 === 0) ? backgroundTileColor1 : backgroundTileColor2;
                } else {
                    return (gridY % 2 === 0) ? backgroundTileColor2 : backgroundTileColor1;
                }
            }
        }
    }

    // BOUNDARY WALLS
    Repeater {
        // Total number of wall squares along the 4 edges:
        // Left edge: gridRowCount squares
        // Right edge: gridRowCount squares
        // Top edge: gridColumnCount - 2 squares (exclude corners)
        // Bottom edge: gridColumnCount - 2 squares (exclude corners)
        model: (2 * gridRowCount) + (2 * (gridColumnCount - 2))

        delegate: Item {
            Wall {
                width: tileSize
                height: tileSize
                tileSize: arena.tileSize

                // helper constants
                property int totalRows: gridRowCount
                property int totalColumns: gridColumnCount
                property int leftEdgeCount: totalRows
                property int rightEdgeCount: totalRows
                property int topEdgeCount: totalColumns - 2

                // compute grid coordinates FROM index
                property int gridX: {
                    if (index < leftEdgeCount) {
                        return 0
                    } else if (index < leftEdgeCount + rightEdgeCount) {
                        return totalColumns - 1
                    } else if (index < leftEdgeCount + rightEdgeCount + topEdgeCount) {
                        return 1 + (index - leftEdgeCount - rightEdgeCount)
                    } else {
                        return 1 + (index - leftEdgeCount - rightEdgeCount - topEdgeCount)
                    }
                }

                property int gridY: {
                    if (index < leftEdgeCount) {
                        return index
                    } else if (index < leftEdgeCount + rightEdgeCount) {
                        return index - leftEdgeCount
                    } else if (index < leftEdgeCount + rightEdgeCount + topEdgeCount) {
                        return 0
                    } else {
                        return totalRows - 1
                    }
                }

                // convert grid to pixels
                x: gridX * tileSize
                y: gridY * tileSize
            }
        }
    }
}
