#pragma once

#include <QObject>
#include <QVector>
#include <QPoint>
#include <QDebug>
#include <QGraphicsRectItem>
#include "drawer.h"

class Snake
{
public:
    /*Forward declaration*/
    enum class Direction;

    Snake();
    void Move();
    bool IsMovePossible();
    void Grow();
    void Reset();

    void SetHeadPosition(QPoint headPosition) {m_HeadPosition = headPosition;}
    void SetDirection(Direction direction) {m_Direction = direction;}
    void SetNextDirection(Direction nextDirection) {m_NextDirection = nextDirection;}
    void SetSnakeSquaresGraphicalRectItems(QVector<QGraphicsRectItem*> const& snakeSquaresGraphicalRectItems)
    {m_SnakeSquaresGraphicalRectItems = snakeSquaresGraphicalRectItems;}

    QVector<QPoint>& GetPositions() {return m_Positions;}
    QPoint& GetHeadPosition() {return m_HeadPosition;}
    Direction& GetDirection() {return m_Direction;}
    Direction& GetNextDirection() {return m_NextDirection;}
    QVector<QGraphicsRectItem*>& GetSnakeSquaresGraphicalRectItems() {return m_SnakeSquaresGraphicalRectItems;}

    enum class Direction
    {
        left = 1,
        up = 2,
        down = 3,
        right = 4
    };

private:
    Direction m_Direction;
    Direction m_NextDirection;
    QPoint m_HeadPosition;
    QVector<QPoint> m_Positions;
    QVector<QPoint> m_StartingPositions = {QPoint(Drawer::COLUMNS_COUNT/2 + 2, Drawer::ROWS_COUNT/2),
                                           QPoint(Drawer::COLUMNS_COUNT/2 + 1, Drawer::ROWS_COUNT/2),
                                           QPoint(Drawer::COLUMNS_COUNT/2, Drawer::ROWS_COUNT/2)};

    QVector<QGraphicsRectItem*> m_SnakeSquaresGraphicalRectItems;
};
