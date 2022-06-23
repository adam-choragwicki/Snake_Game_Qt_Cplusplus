#pragma once

#include "snake.h"
#include "food.h"

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QVector>

class Drawer
{
public:
    Drawer() = delete;
    Drawer(const Drawer&) = delete;
    Drawer& operator=(const Drawer&) = delete;
    Drawer(Drawer&&) = delete;
    Drawer& operator=(Drawer&&) = delete;

    static void setScene(QGraphicsScene* scene) {scene_ = scene;}
    static void drawSnake(Snake& snake);
    static void eraseSnake(Snake& snake);
    static void redrawSnake(Snake& snake);
    static void drawFood(Food& food);
    static void eraseFood(Food& food);
    static void drawGameArena();
    [[maybe_unused]] static void drawAllSquares();

private:
    static void drawEyes(Snake& snake, int eye1XOffset, int eye1YOffset, int eye2XOffset, int eye2YOffset);

    inline static QGraphicsScene* scene_ {};
};
