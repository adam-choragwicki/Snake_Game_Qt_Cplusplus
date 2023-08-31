#pragma once

#include "model/snake.h"
#include "model/model.h"

#include <QWidget>
#include <QPainter>

class GameArena : public QWidget
{
public:
    explicit GameArena(QWidget* parent, const Model& model);
    void paintEvent([[maybe_unused]] QPaintEvent* event) override;

private:
    void drawGameArena(QPainter& painter) const;
    void drawSnakeSegment(QPainter& painter, const Coordinates& coordinates) const;
    void drawSnake(QPainter& painter, const Snake& snake) const;
    void drawSnakeHead(QPainter& painter, const Snake& snake) const;
    void drawSnakeEyes(QPainter& painter, const Snake& snake) const;
    void drawFood(QPainter& painter, const Food& food) const;

    [[maybe_unused]] void drawAllPossibleSquares(QPainter& painter);

    const Model& model_;
};
