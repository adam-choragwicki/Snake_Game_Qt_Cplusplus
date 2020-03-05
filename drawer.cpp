#include "drawer.h"
#include "utilities.h"

Drawer::Drawer(QGraphicsScene* pScene)
{
    m_pScene = pScene;
}

void Drawer::DrawSnake(QVector<QPoint> positions)
{
    QPen redPen(Qt::red);
    QBrush greenBrush(Qt::green);

    //fill queue with drawn items
    for(auto position : positions)
    {
        m_DrawnItems.append(m_pScene->addRect(position.x() * SQUARE_SIZE  + SQUARE_SIZE,
                                              position.y() * SQUARE_SIZE  + SQUARE_SIZE,
                                              SQUARE_SIZE,
                                              SQUARE_SIZE,
                                              redPen,
                                              greenBrush));
    }
}

void Drawer::EraseSnake()
{
    for(auto item : m_DrawnItems)
    {
        m_pScene->removeItem(item);
    }

    m_DrawnItems.clear();
    m_DrawnItems.squeeze();
}

void Drawer::DrawFood(QPoint foodPosition)
{
    QPen redPen(Qt::red);
    QBrush redBrush(Qt::red);

    m_pDrawnFood = m_pScene->addRect(foodPosition.x() * SQUARE_SIZE + SQUARE_SIZE,
                                     foodPosition.y() * SQUARE_SIZE + SQUARE_SIZE,
                                     SQUARE_SIZE,
                                     SQUARE_SIZE,
                                     redPen,
                                     redBrush);
}

void Drawer::EraseFood()
{
    m_pScene->removeItem(m_pDrawnFood);
}
