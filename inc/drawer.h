#pragma once

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QVector>
#include <QPoint>

class Drawer
{
public:
    Drawer() = delete;
    Drawer(Drawer const&) = delete;
    Drawer& operator=(Drawer&) = delete;
    Drawer(Drawer const&&) = delete;
    Drawer& operator=(Drawer&&) = delete;

    static void SetScene(QGraphicsScene* pScene) {m_pScene = pScene;}
    static void DrawSnake(const QVector<QPoint> &snakeSquarePositions, QVector<QGraphicsRectItem *> &snakeSquaresGraphicalRectItems);
    static void EraseSnake(QVector<QGraphicsRectItem*>& snakeSquaresGraphicalRectItems);
    static QGraphicsRectItem* DrawFood(QPoint foodPosition);
    static void EraseFood(QGraphicsRectItem* pFoodSquareGraphicalRectItem);
    static void DrawAllSquares();
    static void DrawGameArena();

    static const int SQUARE_SIZE = 30;
    static const int ROWS_COUNT = 25;
    static const int COLUMNS_COUNT = 50;

    /*Do not modify beyond this point*/
    static const int WALL_THICKNESS = SQUARE_SIZE;
    static const int MINIMUM_ROW_COLUMN = 0;
    static const int MAXIMUM_ROW = ROWS_COUNT - 1;
    static const int MAXIMUM_COLUMN = COLUMNS_COUNT - 1;

    static const int LEFT_BORDER_X = SQUARE_SIZE/2;
    static const int RIGHT_BORDER_X = COLUMNS_COUNT * SQUARE_SIZE + 2 * WALL_THICKNESS;
    static const int RIGHT_BORDER_X_OFFSET = -SQUARE_SIZE/2;
    static const int TOP_Y = SQUARE_SIZE/2;
    static const int BOTTOM_Y = ROWS_COUNT * SQUARE_SIZE + 2 * WALL_THICKNESS;
    static const int BOTTOM_Y_OFFSET = -SQUARE_SIZE/2;

private:
    static QGraphicsScene* m_pScene;
};
