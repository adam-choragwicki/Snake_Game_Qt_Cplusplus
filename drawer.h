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

private:
    static QGraphicsScene* m_pScene;
};
