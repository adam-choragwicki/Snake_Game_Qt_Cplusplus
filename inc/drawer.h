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
    Drawer(const Drawer&) = delete;
    Drawer& operator=(const Drawer&) = delete;
    Drawer(Drawer&&) = delete;
    Drawer& operator=(Drawer&&) = delete;

    static void setScene(QGraphicsScene* scene) {scene_ = scene;}
    static void drawSnake(const QVector<QPoint>& snakeSquarePositions, QVector<QGraphicsRectItem*>& snakeSquaresGraphicalRectItems);
    static void eraseSnake(QVector<QGraphicsRectItem*>& snakeSquaresGraphicalRectItems);
    static QGraphicsRectItem* drawFood(QPoint foodPosition);
    static void eraseFood(QGraphicsRectItem* pFoodSquareGraphicalRectItem);
    [[maybe_unused]] static void drawAllSquares();
    static void drawGameArena();

private:
    static QGraphicsScene* scene_;
};
