#pragma once

#include "snake.h"
#include "model.h"

#include <QWidget>
#include <QPainter>

class GameArena : public QWidget
{
public slots:
    void updateArena();

public:
    explicit GameArena(QWidget* parent, Model* model);
    void paintEvent([[maybe_unused]] QPaintEvent* event) override;

private:
    void drawGameArena(QPainter& painter) const;
    void drawSnake(QPainter& painter) const;
    void drawSnakeHead(QPainter& painter, Snake* snake) const;
    void drawSnakeSegment(QPainter& painter, SnakeSegment* snakeSegment) const;
    void drawSnakeEyes(QPainter& painter, Snake* snake) const;
    void drawFood(QPainter& painter) const;
    void drawFoodInsideSnake(QPainter& painter, SnakeSegment* snakeSegment) const;

    [[maybe_unused]] static void drawAllSquares(QPainter& painter);

    Model* model_;
};
