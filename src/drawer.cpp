#include "drawer.h"
#include "common.h"

void Drawer::drawSnake(const QVector<QPoint>& snakeSquarePositions, QVector<QGraphicsRectItem*>& snakeSquaresGraphicalRectItems)
{
    QPen redPen(Qt::red);
    QBrush yellowBrush(Qt::yellow);
    QBrush greenBrush(Qt::green);

    for(auto& snakeSquarePosition : snakeSquarePositions)
    {
        snakeSquaresGraphicalRectItems.append(scene_->addRect(snakeSquarePosition.x() * GameArenaParameters::snakeSegmentSize + GameArenaParameters::snakeSegmentSize,
                                                              snakeSquarePosition.y() * GameArenaParameters::snakeSegmentSize + GameArenaParameters::snakeSegmentSize,
                                                              GameArenaParameters::snakeSegmentSize,
                                                              GameArenaParameters::snakeSegmentSize,
                                                              redPen,
                                                              greenBrush));
    }

    /*Set head color*/
    snakeSquaresGraphicalRectItems.at(0)->setBrush(yellowBrush);
}

void Drawer::eraseSnake(QVector<QGraphicsRectItem*>& snakeSquaresGraphicalRectItems)
{
    for(auto& snakeSquaresGraphicalRectItem : snakeSquaresGraphicalRectItems)
    {
        scene_->removeItem(snakeSquaresGraphicalRectItem);
    }

    snakeSquaresGraphicalRectItems.clear();
    snakeSquaresGraphicalRectItems.squeeze();
}

QGraphicsEllipseItem* Drawer::drawFood(const QPoint& foodPosition)
{
    QPen redPen(Qt::red);
    QBrush redBrush(Qt::red);

    QGraphicsEllipseItem* pFoodGraphicalEllipseItem = scene_->addEllipse(foodPosition.x() * GameArenaParameters::snakeSegmentSize + GameArenaParameters::snakeSegmentSize + GameArenaParameters::foodOffset,
                                                                         foodPosition.y() * GameArenaParameters::snakeSegmentSize + GameArenaParameters::snakeSegmentSize + GameArenaParameters::foodOffset,
                                                                         GameArenaParameters::foodSize,
                                                                         GameArenaParameters::foodSize,
                                                                         redPen,
                                                                         redBrush);

    return pFoodGraphicalEllipseItem;
}

void Drawer::eraseFood(QGraphicsEllipseItem* pFoodSquareGraphicalEllipseItem)
{
    scene_->removeItem(pFoodSquareGraphicalEllipseItem);
}

[[maybe_unused]] void Drawer::drawAllSquares()
{
    QBrush redBrush(Qt::red);
    QBrush greenBrush(Qt::green);

    for(int column = 0 ; column < GameArenaParameters::columnCount; column++)
    {
        for(int row = 0; row < GameArenaParameters::rowsCount; row++)
        {
            /*Even columns*/
            if(column % 2 == 0)
            {
                if(row % 2 == 0)
                {
                    scene_->addRect(column * GameArenaParameters::snakeSegmentSize + GameArenaParameters::snakeSegmentSize,
                                    row * GameArenaParameters::snakeSegmentSize + GameArenaParameters::snakeSegmentSize,
                                    GameArenaParameters::snakeSegmentSize,
                                    GameArenaParameters::snakeSegmentSize,
                                    Qt::NoPen,
                                    redBrush);
                }
                else
                {
                    scene_->addRect(column * GameArenaParameters::snakeSegmentSize + GameArenaParameters::snakeSegmentSize,
                                    row * GameArenaParameters::snakeSegmentSize + GameArenaParameters::snakeSegmentSize,
                                    GameArenaParameters::snakeSegmentSize,
                                    GameArenaParameters::snakeSegmentSize,
                                    Qt::NoPen,
                                    greenBrush);
                }
            }
            /*Odd columns*/
            else
            {
                if(row % 2 == 0)
                {
                    scene_->addRect(column * GameArenaParameters::snakeSegmentSize + GameArenaParameters::snakeSegmentSize,
                                    row * GameArenaParameters::snakeSegmentSize + GameArenaParameters::snakeSegmentSize,
                                    GameArenaParameters::snakeSegmentSize,
                                    GameArenaParameters::snakeSegmentSize,
                                    Qt::NoPen,
                                    greenBrush);
                }
                else
                {
                    scene_->addRect(column * GameArenaParameters::snakeSegmentSize + GameArenaParameters::snakeSegmentSize,
                                    row * GameArenaParameters::snakeSegmentSize + GameArenaParameters::snakeSegmentSize,
                                    GameArenaParameters::snakeSegmentSize,
                                    GameArenaParameters::snakeSegmentSize,
                                    Qt::NoPen,
                                    redBrush);
                }
            }
        }
    }
}

void Drawer::drawGameArena()
{
    QPen pen(Qt::white, GameArenaParameters::snakeSegmentSize);

    /*Top wall*/
    scene_->addLine(GameArenaParameters::leftBorderX,
                    GameArenaParameters::topY,
                    GameArenaParameters::rightBorderX + GameArenaParameters::rightBorderXOffset,
                    GameArenaParameters::topY,
                    pen);
    /*Left wall*/
    scene_->addLine(GameArenaParameters::leftBorderX,
                    GameArenaParameters::topY,
                    GameArenaParameters::leftBorderX,
                    GameArenaParameters::bottomY + GameArenaParameters::bottomYOffset,
                    pen);
    /*Bottom wall*/
    scene_->addLine(GameArenaParameters::leftBorderX,
                    GameArenaParameters::bottomY + GameArenaParameters::bottomYOffset,
                    GameArenaParameters::rightBorderX + GameArenaParameters::rightBorderXOffset,
                    GameArenaParameters::bottomY + GameArenaParameters::bottomYOffset,
                    pen);
    /*Right wall*/
    scene_->addLine(GameArenaParameters::rightBorderX + GameArenaParameters::rightBorderXOffset,
                    GameArenaParameters::topY,
                    GameArenaParameters::rightBorderX + GameArenaParameters::rightBorderXOffset,
                    GameArenaParameters::bottomY + GameArenaParameters::bottomYOffset,
                    pen);
}
