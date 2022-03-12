#include "drawer.h"
#include "common.h"

void Drawer::drawSnake(Snake& snake)
{
    static const QBrush headBrush(Snake::headColor);
    static const QBrush bodyBrush(Snake::bodyColor);
    static const QBrush foodInsideBrush(Qt::red);

    const QVector<Snake::Segment>& snakeSegments = snake.getSegments();

    QVector<QGraphicsRectItem*>& snakeSquaresGraphicalRectItems = snake.getSnakeSquaresGraphicalRectItems();
    QVector<QGraphicsEllipseItem*>& snakeSquaresGraphicalEllipseItems = snake.getSnakeSquaresGraphicalEllipseItem();

    for(auto& snakeSegment: snakeSegments)
    {
        snakeSquaresGraphicalRectItems.append(scene_->addRect(snakeSegment.getCoordinates().x() * GameArenaParameters::snakeSegmentSize + GameArenaParameters::snakeSegmentSize,
                                                              snakeSegment.getCoordinates().y() * GameArenaParameters::snakeSegmentSize + GameArenaParameters::snakeSegmentSize,
                                                              GameArenaParameters::snakeSegmentSize,
                                                              GameArenaParameters::snakeSegmentSize,
                                                              Qt::NoPen,
                                                              bodyBrush));

        if(snakeSegment.isFoodInside())
        {
            snakeSquaresGraphicalEllipseItems.append(scene_->addEllipse(snakeSegment.getCoordinates().x() * GameArenaParameters::snakeSegmentSize + GameArenaParameters::snakeSegmentSize + GameArenaParameters::foodOffset,
                                                                        snakeSegment.getCoordinates().y() * GameArenaParameters::snakeSegmentSize + GameArenaParameters::snakeSegmentSize + GameArenaParameters::foodOffset,
                                                                        static_cast<int>(GameArenaParameters::snakeSegmentSize / 2),
                                                                        static_cast<int>(GameArenaParameters::snakeSegmentSize / 2),
                                                                        Qt::NoPen,
                                                                        foodInsideBrush));
        }
    }

    /*Set head color*/
    snakeSquaresGraphicalRectItems.at(0)->setBrush(headBrush);
}

void Drawer::eraseSnake(Snake& snake)
{
    QVector<QGraphicsRectItem*>& snakeSquaresGraphicalRectItems = snake.getSnakeSquaresGraphicalRectItems();
    QVector<QGraphicsEllipseItem*>& snakeSquaresGraphicalEllipseItems = snake.getSnakeSquaresGraphicalEllipseItem();

    for(auto& snakeSquaresGraphicalRectItem: snakeSquaresGraphicalRectItems)
    {
        if(snakeSquaresGraphicalRectItem)
        {
            scene_->removeItem(snakeSquaresGraphicalRectItem);
        }
    }

    for(auto& snakeSquaresGraphicalEllipseItem: snakeSquaresGraphicalEllipseItems)
    {
        if(snakeSquaresGraphicalEllipseItem)
        {
            scene_->removeItem(snakeSquaresGraphicalEllipseItem);
        }

        snakeSquaresGraphicalEllipseItem = nullptr;
    }

    snakeSquaresGraphicalEllipseItems.clear();
    snakeSquaresGraphicalRectItems.clear();
}

void Drawer::redrawSnake(Snake& snake)
{
    eraseSnake(snake);
    drawSnake(snake);
}

void Drawer::drawFood(Food& food)
{
    static const QPen outlinePen(Qt::red);
    static const QBrush brush(Food::color);

    const QPoint& foodPosition = food.getPosition();
    QGraphicsEllipseItem*& foodGraphicalEllipseItem = food.getFoodGraphicalEllipseItem();

    foodGraphicalEllipseItem = scene_->addEllipse(foodPosition.x() * GameArenaParameters::snakeSegmentSize + GameArenaParameters::snakeSegmentSize + GameArenaParameters::foodOffset,
                                                  foodPosition.y() * GameArenaParameters::snakeSegmentSize + GameArenaParameters::snakeSegmentSize + GameArenaParameters::foodOffset,
                                                  GameArenaParameters::foodSize,
                                                  GameArenaParameters::foodSize,
                                                  outlinePen,
                                                  brush);
}

void Drawer::eraseFood(Food& food)
{
    QGraphicsEllipseItem*& foodGraphicalEllipseItem = food.getFoodGraphicalEllipseItem();

    scene_->removeItem(food.getFoodGraphicalEllipseItem());
    foodGraphicalEllipseItem = nullptr;
}

void Drawer::drawGameArena()
{
    static const QPen outlinePen(Qt::white, GameArenaParameters::snakeSegmentSize);

    /*Top wall*/
    scene_->addLine(GameArenaParameters::leftBorderX,
                    GameArenaParameters::topY,
                    GameArenaParameters::rightBorderX + GameArenaParameters::rightBorderXOffset,
                    GameArenaParameters::topY,
                    outlinePen);
    /*Left wall*/
    scene_->addLine(GameArenaParameters::leftBorderX,
                    GameArenaParameters::topY,
                    GameArenaParameters::leftBorderX,
                    GameArenaParameters::bottomY + GameArenaParameters::bottomYOffset,
                    outlinePen);
    /*Bottom wall*/
    scene_->addLine(GameArenaParameters::leftBorderX,
                    GameArenaParameters::bottomY + GameArenaParameters::bottomYOffset,
                    GameArenaParameters::rightBorderX + GameArenaParameters::rightBorderXOffset,
                    GameArenaParameters::bottomY + GameArenaParameters::bottomYOffset,
                    outlinePen);
    /*Right wall*/
    scene_->addLine(GameArenaParameters::rightBorderX + GameArenaParameters::rightBorderXOffset,
                    GameArenaParameters::topY,
                    GameArenaParameters::rightBorderX + GameArenaParameters::rightBorderXOffset,
                    GameArenaParameters::bottomY + GameArenaParameters::bottomYOffset,
                    outlinePen);
}

[[maybe_unused]] void Drawer::drawAllSquares()
{
    static const QBrush redBrush(Qt::red);
    static const QBrush greenBrush(Qt::green);

    for(int column = 0; column < GameArenaParameters::columnCount; column++)
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
