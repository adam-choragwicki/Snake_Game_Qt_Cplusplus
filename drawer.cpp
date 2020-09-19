#include "drawer.h"
#include <QDebug>

QGraphicsScene* Drawer::m_pScene = nullptr;

void Drawer::DrawSnake(QVector<QPoint> const& snakeSquarePositions, QVector<QGraphicsRectItem*>& snakeSquaresGraphicalRectItems)
{
    QPen redPen(Qt::red);
    QBrush yellowBrush(Qt::yellow);
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

    /*Set head color*/
    snakeSquaresGraphicalRectItems.at(0)->setBrush(yellowBrush);
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

void Drawer::DrawAllSquares()
{
    QBrush redBrush(Qt::red);
    QBrush greenBrush(Qt::green);

    for(int column = 0 ; column < COLUMNS_COUNT; column++)
    {
        for(int row = 0; row < ROWS_COUNT; row++)
        {
            /*Even columns*/
            if(column % 2 == 0)
            {
                if(row % 2 == 0)
                {
                    m_pScene->addRect(column * SQUARE_SIZE + SQUARE_SIZE,
                                    row * SQUARE_SIZE + SQUARE_SIZE,
                                    SQUARE_SIZE,
                                    SQUARE_SIZE,
                                    Qt::NoPen,
                                    redBrush);
                }
                else
                {
                    m_pScene->addRect(column * SQUARE_SIZE + SQUARE_SIZE,
                                    row * SQUARE_SIZE + SQUARE_SIZE,
                                    SQUARE_SIZE,
                                    SQUARE_SIZE,
                                    Qt::NoPen,
                                    greenBrush);
                }
            }
            /*Odd columns*/
            else
            {
                if(row % 2 == 0)
                {
                    m_pScene->addRect(column * SQUARE_SIZE + SQUARE_SIZE,
                                    row * SQUARE_SIZE + SQUARE_SIZE,
                                    SQUARE_SIZE,
                                    SQUARE_SIZE,
                                    Qt::NoPen,
                                    greenBrush);
                }
                else
                {
                    m_pScene->addRect(column * SQUARE_SIZE + SQUARE_SIZE,
                                    row * SQUARE_SIZE + SQUARE_SIZE,
                                    SQUARE_SIZE,
                                    SQUARE_SIZE,
                                    Qt::NoPen,
                                    redBrush);
                }
            }
        }
    }
}

void Drawer::DrawGameArena()
{
    QPen pen(Qt::white, SQUARE_SIZE);

    /*Top wall*/
    m_pScene->addLine(LEFT_BORDER_X,
                    TOP_Y,
                    RIGHT_BORDER_X + RIGHT_BORDER_X_OFFSET,
                    TOP_Y,
                    pen);
    /*Left wall*/
    m_pScene->addLine(LEFT_BORDER_X,
                    TOP_Y,
                    LEFT_BORDER_X,
                    BOTTOM_Y + BOTTOM_Y_OFFSET,
                    pen);
    /*Bottom wall*/
    m_pScene->addLine(LEFT_BORDER_X,
                    BOTTOM_Y + BOTTOM_Y_OFFSET,
                    RIGHT_BORDER_X + RIGHT_BORDER_X_OFFSET,
                    BOTTOM_Y + BOTTOM_Y_OFFSET,
                    pen);
    /*Right wall*/
    m_pScene->addLine(RIGHT_BORDER_X + RIGHT_BORDER_X_OFFSET,
                    TOP_Y,
                    RIGHT_BORDER_X + RIGHT_BORDER_X_OFFSET,
                    BOTTOM_Y + BOTTOM_Y_OFFSET,
                    pen);
}
