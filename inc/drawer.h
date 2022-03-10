#pragma once

#include "snake.h"
#include "food.h"

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
    static void redrawSnake(Snake& snake);
    static void drawFood(Food& food);
    static void eraseFood(Food& food);
    static void drawGameArena();
    [[maybe_unused]] static void drawAllSquares();

private:
    static void drawSnake(Snake& snake);
    static void eraseSnake(Snake& snake);

    inline static QGraphicsScene* scene_ {};
};
