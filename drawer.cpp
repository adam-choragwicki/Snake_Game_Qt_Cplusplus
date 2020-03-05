#include "drawer.h"
#include "utilities.h"

QGraphicsScene* Drawer::m_pScene = nullptr;
QVector<QGraphicsRectItem*> Drawer::m_SnakeSquaresGraphicalRectItems;
QGraphicsRectItem* Drawer::m_pFoodSquareGraphicalRectItem = nullptr;

void Drawer::DrawSnake(QVector<QPoint> const& snakeSquarePositions)
{
    QPen redPen(Qt::red);
    QBrush greenBrush(Qt::green);

    for(auto snakeSquarePosition : snakeSquarePositions)
    {
        m_SnakeSquaresGraphicalRectItems.append(m_pScene->addRect(snakeSquarePosition.x() * SQUARE_SIZE  + SQUARE_SIZE,
                                                                  snakeSquarePosition.y() * SQUARE_SIZE  + SQUARE_SIZE,
                                                                  SQUARE_SIZE,
                                                                  SQUARE_SIZE,
                                                                  redPen,
                                                                  greenBrush));
    }
}

void Drawer::EraseSnake()
{
    for(auto item : m_SnakeSquaresGraphicalRectItems)
    {
        m_pScene->removeItem(item);
    }

    m_SnakeSquaresGraphicalRectItems.clear();
    m_SnakeSquaresGraphicalRectItems.squeeze();
}

void Drawer::DrawFood(QPoint foodPosition)
{
    QPen redPen(Qt::red);
    QBrush redBrush(Qt::red);

    m_pFoodSquareGraphicalRectItem = m_pScene->addRect(foodPosition.x() * SQUARE_SIZE + SQUARE_SIZE,
                                                       foodPosition.y() * SQUARE_SIZE + SQUARE_SIZE,
                                                       SQUARE_SIZE,
                                                       SQUARE_SIZE,
                                                       redPen,
                                                       redBrush);
}

void Drawer::EraseFood()
{
    m_pScene->removeItem(m_pFoodSquareGraphicalRectItem);
}
