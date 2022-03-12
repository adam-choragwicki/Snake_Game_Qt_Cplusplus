#include "drawer.h"
#include "common.h"

void Drawer::drawSnake(Snake& snake)
{
    static const QBrush snakeHeadBrush(Snake::headColor);
    static const QBrush snakeBodyBrush(Snake::bodyColor);
    static const QBrush foodInsideSnakeBrush(Qt::red);

    const QVector<Snake::Segment>& snakeSegments = snake.getSegments();

    QVector<QGraphicsRectItem*>& snakeSquaresGraphicalRectItems = snake.getSnakeSquaresGraphicalRectItems();
    QVector<QGraphicsEllipseItem*>& snakeSquaresGraphicalEllipseItems = snake.getSnakeSquaresGraphicalEllipseItem();

    for(auto& snakeSegment: snakeSegments)
    {
        snakeSquaresGraphicalRectItems.append(scene_->addRect(snakeSegment.getCoordinates().x() * GameParameters::snakeSegmentSize + GameParameters::snakeSegmentSize,
                                                              snakeSegment.getCoordinates().y() * GameParameters::snakeSegmentSize + GameParameters::snakeSegmentSize,
                                                              GameParameters::snakeSegmentSize,
                                                              GameParameters::snakeSegmentSize,
                                                              Qt::NoPen,
                                                              snakeBodyBrush));

        if(snakeSegment.isFoodInside())
        {
            snakeSquaresGraphicalEllipseItems.append(scene_->addEllipse(snakeSegment.getCoordinates().x() * GameParameters::snakeSegmentSize + GameParameters::snakeSegmentSize + GameParameters::foodInsideSnakeOffset,
                                                                        snakeSegment.getCoordinates().y() * GameParameters::snakeSegmentSize + GameParameters::snakeSegmentSize + GameParameters::foodInsideSnakeOffset,
                                                                        GameParameters::foodInsideSnakeSize,
                                                                        GameParameters::foodInsideSnakeSize,
                                                                        Qt::NoPen,
                                                                        foodInsideSnakeBrush));
        }
    }

    /*Set head color*/
    snakeSquaresGraphicalRectItems.at(0)->setBrush(snakeHeadBrush);
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

    foodGraphicalEllipseItem = scene_->addEllipse(foodPosition.x() * GameParameters::snakeSegmentSize + GameParameters::snakeSegmentSize + GameParameters::foodInsideSnakeOffset,
                                                  foodPosition.y() * GameParameters::snakeSegmentSize + GameParameters::snakeSegmentSize + GameParameters::foodInsideSnakeOffset,
                                                  GameParameters::foodSize,
                                                  GameParameters::foodSize,
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
