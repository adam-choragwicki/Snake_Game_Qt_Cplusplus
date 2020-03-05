#include "drawer.h"
#include "utilities.h"
#include <QDebug>

QGraphicsScene* Drawer::m_pScene = nullptr;

void Drawer::DrawSnake(QVector<QPoint> const& snakeSquarePositions, QVector<QGraphicsRectItem*>& snakeSquaresGraphicalRectItems)
{
    QPen redPen(Qt::red);
    QBrush greenBrush(Qt::green);

    for(auto snakeSquarePosition : snakeSquarePositions)
    {
        snakeSquaresGraphicalRectItems.append(m_pScene->addRect(snakeSquarePosition.x() * SQUARE_SIZE  + SQUARE_SIZE,
                                                                snakeSquarePosition.y() * SQUARE_SIZE  + SQUARE_SIZE,
                                                                SQUARE_SIZE,
                                                                SQUARE_SIZE,
                                                                redPen,
                                                                greenBrush));
    }
}

void Drawer::EraseSnake(QVector<QGraphicsRectItem*>& snakeSquaresGraphicalRectItems)
{
    for(auto item : snakeSquaresGraphicalRectItems)
    {
        m_pScene->removeItem(item);
    }

    snakeSquaresGraphicalRectItems.clear();
    snakeSquaresGraphicalRectItems.squeeze();
}

QGraphicsRectItem* Drawer::DrawFood(QPoint foodPosition)
{
    QPen redPen(Qt::red);
    QBrush redBrush(Qt::red);

    QGraphicsRectItem* pFoodSquareGraphicalRectItem = m_pScene->addRect(foodPosition.x() * SQUARE_SIZE + SQUARE_SIZE,
                                                     foodPosition.y() * SQUARE_SIZE + SQUARE_SIZE,
                                                     SQUARE_SIZE,
                                                     SQUARE_SIZE,
                                                     redPen,
                                                     redBrush);

    return pFoodSquareGraphicalRectItem;
}

void Drawer::EraseFood(QGraphicsRectItem* pFoodSquareGraphicalRectItem)
{
    m_pScene->removeItem(pFoodSquareGraphicalRectItem);
}
