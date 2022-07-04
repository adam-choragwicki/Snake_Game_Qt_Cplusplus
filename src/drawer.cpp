#include "drawer.h"
#include "config.h"

void Drawer::drawItem(QGraphicsItem* graphicsItem)
{
    scene_->addItem(graphicsItem);
}

void Drawer::eraseItem(QGraphicsItem* graphicsItem)
{
    scene_->removeItem(graphicsItem);
}

void Drawer::drawGameArena()
{
    static const QPen outlinePen(Qt::white, GameParameters::snakeSegmentSize);

    /*Top wall*/
    scene_->addLine(GameParameters::Arena::leftBorderX,
                    GameParameters::Arena::topY,
                    GameParameters::Arena::rightBorderX + GameParameters::Arena::rightBorderXOffset,
                    GameParameters::Arena::topY,
                    outlinePen);
    /*Left wall*/
    scene_->addLine(GameParameters::Arena::leftBorderX,
                    GameParameters::Arena::topY,
                    GameParameters::Arena::leftBorderX,
                    GameParameters::Arena::bottomY + GameParameters::Arena::bottomYOffset,
                    outlinePen);
    /*Bottom wall*/
    scene_->addLine(GameParameters::Arena::leftBorderX,
                    GameParameters::Arena::bottomY + GameParameters::Arena::bottomYOffset,
                    GameParameters::Arena::rightBorderX + GameParameters::Arena::rightBorderXOffset,
                    GameParameters::Arena::bottomY + GameParameters::Arena::bottomYOffset,
                    outlinePen);
    /*Right wall*/
    scene_->addLine(GameParameters::Arena::rightBorderX + GameParameters::Arena::rightBorderXOffset,
                    GameParameters::Arena::topY,
                    GameParameters::Arena::rightBorderX + GameParameters::Arena::rightBorderXOffset,
                    GameParameters::Arena::bottomY + GameParameters::Arena::bottomYOffset,
                    outlinePen);
}

void Drawer::updateScene()
{
    scene_->update();
}

[[maybe_unused]] void Drawer::drawAllSquares()
{
    static const QBrush redBrush(Qt::red);
    static const QBrush greenBrush(Qt::green);

    for(int column = 0; column < GameParameters::Arena::columnCount; column++)
    {
        for(int row = 0; row < GameParameters::Arena::rowsCount; row++)
        {
            /*Even columns*/
            if(column % 2 == 0)
            {
                if(row % 2 == 0)
                {
                    scene_->addRect(column * GameParameters::snakeSegmentSize + GameParameters::snakeSegmentSize,
                                    row * GameParameters::snakeSegmentSize + GameParameters::snakeSegmentSize,
                                    GameParameters::snakeSegmentSize,
                                    GameParameters::snakeSegmentSize,
                                    Qt::NoPen,
                                    redBrush);
                }
                else
                {
                    scene_->addRect(column * GameParameters::snakeSegmentSize + GameParameters::snakeSegmentSize,
                                    row * GameParameters::snakeSegmentSize + GameParameters::snakeSegmentSize,
                                    GameParameters::snakeSegmentSize,
                                    GameParameters::snakeSegmentSize,
                                    Qt::NoPen,
                                    greenBrush);
                }
            }
                /*Odd columns*/
            else
            {
                if(row % 2 == 0)
                {
                    scene_->addRect(column * GameParameters::snakeSegmentSize + GameParameters::snakeSegmentSize,
                                    row * GameParameters::snakeSegmentSize + GameParameters::snakeSegmentSize,
                                    GameParameters::snakeSegmentSize,
                                    GameParameters::snakeSegmentSize,
                                    Qt::NoPen,
                                    greenBrush);
                }
                else
                {
                    scene_->addRect(column * GameParameters::snakeSegmentSize + GameParameters::snakeSegmentSize,
                                    row * GameParameters::snakeSegmentSize + GameParameters::snakeSegmentSize,
                                    GameParameters::snakeSegmentSize,
                                    GameParameters::snakeSegmentSize,
                                    Qt::NoPen,
                                    redBrush);
                }
            }
        }
    }
}
