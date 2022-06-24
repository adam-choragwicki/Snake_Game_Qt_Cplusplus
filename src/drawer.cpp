#include "drawer.h"
#include "common.h"

void Drawer::drawSnake(Snake& snake)
{
    static const QBrush snakeHeadBrush(GameParameters::snakeHeadColor);
    static const QBrush snakeBodyBrush(GameParameters::snakeBodyColor);
    static const QBrush foodInsideSnakeBrush(GameParameters::snakeEyesColor);

    const QVector<SnakeSegment*>& snakeSegments = snake.getSegments();

    QVector<QGraphicsRectItem*>& snakeSegmentsGraphicalRectItems = snake.getSnakeSegmentsGraphicalRectItems();
    QVector<QGraphicsEllipseItem*>& foodInsideSnakeGraphicalEllipseItems = snake.getFoodInsideSnakeGraphicalEllipseItem();

    for(auto& snakeSegment: snakeSegments)
    {
        snakeSegmentsGraphicalRectItems.append(scene_->addRect(snakeSegment->getCoordinates().x * GameParameters::snakeSegmentSize + GameParameters::snakeSegmentSize,
                                                               snakeSegment->getCoordinates().y * GameParameters::snakeSegmentSize + GameParameters::snakeSegmentSize,
                                                               GameParameters::snakeSegmentSize,
                                                               GameParameters::snakeSegmentSize,
                                                               Qt::NoPen,
                                                               snakeBodyBrush));

        if(snakeSegment->isFoodInside())
        {
            foodInsideSnakeGraphicalEllipseItems.append(scene_->addEllipse(snakeSegment->getCoordinates().x * GameParameters::snakeSegmentSize + GameParameters::snakeSegmentSize + GameParameters::foodInsideSnakeOffset,
                                                                        snakeSegment->getCoordinates().y * GameParameters::snakeSegmentSize + GameParameters::snakeSegmentSize + GameParameters::foodInsideSnakeOffset,
                                                                           GameParameters::foodInsideSnakeSize,
                                                                           GameParameters::foodInsideSnakeSize,
                                                                           Qt::NoPen,
                                                                           foodInsideSnakeBrush));
        }
    }

    /*Set head color*/
    snakeSegmentsGraphicalRectItems.at(0)->setBrush(snakeHeadBrush);

    switch(snake.getDirection())
    {
        case Direction::left:
            drawEyes(snake, 5, 5, 5, 20);
            break;

        case Direction::right:
            drawEyes(snake, 20, 5, 20, 20);
            break;

        case Direction::up:
            drawEyes(snake, 5, 5, 20, 5);
            break;

        case Direction::down:
            drawEyes(snake, 5, 20, 20, 20);
            break;
    }
}

void Drawer::drawEyes(Snake& snake, int eye1XOffset, int eye1YOffset, int eye2XOffset, int eye2YOffset)
{
    static const QBrush snakeEyesBrush(GameParameters::snakeEyesColor);

    const QVector<SnakeSegment*>& snakeSegments = snake.getSegments();
    QVector<QGraphicsEllipseItem*>& snakeEyesGraphicalEllipseItems = snake.getSnakeEyesGraphicalEllipseItem();

    snakeEyesGraphicalEllipseItems.append(scene_->addEllipse(snakeSegments.at(0)->getCoordinates().x * GameParameters::snakeSegmentSize + GameParameters::snakeSegmentSize + eye1XOffset,
                                                             snakeSegments.at(0)->getCoordinates().y * GameParameters::snakeSegmentSize + GameParameters::snakeSegmentSize + eye1YOffset,
                                                             GameParameters::snakeEyeSize,
                                                             GameParameters::snakeEyeSize,
                                                             Qt::NoPen,
                                                             snakeEyesBrush));

    snakeEyesGraphicalEllipseItems.append(scene_->addEllipse(snakeSegments.at(0)->getCoordinates().x * GameParameters::snakeSegmentSize + GameParameters::snakeSegmentSize + eye2XOffset,
                                                             snakeSegments.at(0)->getCoordinates().y * GameParameters::snakeSegmentSize + GameParameters::snakeSegmentSize + eye2YOffset,
                                                             GameParameters::snakeEyeSize,
                                                             GameParameters::snakeEyeSize,
                                                             Qt::NoPen,
                                                             snakeEyesBrush));
}

void Drawer::eraseSnake(Snake& snake)
{
    QVector<QGraphicsRectItem*>& snakeSquaresGraphicalRectItems = snake.getSnakeSegmentsGraphicalRectItems();
    QVector<QGraphicsEllipseItem*>& snakeSquaresGraphicalEllipseItems = snake.getFoodInsideSnakeGraphicalEllipseItem();
    QVector<QGraphicsEllipseItem*>& snakeEyesGraphicalEllipseItems = snake.getSnakeEyesGraphicalEllipseItem();

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

    for(auto& snakeEyesGraphicalEllipseItem: snakeEyesGraphicalEllipseItems)
    {
        if(snakeEyesGraphicalEllipseItem)
        {
            scene_->removeItem(snakeEyesGraphicalEllipseItem);
        }

        snakeEyesGraphicalEllipseItem = nullptr;
    }

    snakeSquaresGraphicalEllipseItems.clear();
    snakeSquaresGraphicalRectItems.clear();
    snakeEyesGraphicalEllipseItems.clear();
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

    const Coordinates& foodCoordinates = food.getPosition();

    food.setFoodSquareGraphicalEllipseItem(scene_->addEllipse(foodCoordinates.x * GameParameters::snakeSegmentSize + GameParameters::snakeSegmentSize + GameParameters::foodInsideSnakeOffset,
                                                              foodCoordinates.y * GameParameters::snakeSegmentSize + GameParameters::snakeSegmentSize + GameParameters::foodInsideSnakeOffset,
                                                              GameParameters::foodSize,
                                                              GameParameters::foodSize,
                                                              outlinePen,
                                                              brush));
}

void Drawer::eraseFood(Food& food)
{
    QGraphicsEllipseItem* foodGraphicalEllipseItem = food.getFoodGraphicalEllipseItem();

    if(foodGraphicalEllipseItem)
    {
        scene_->removeItem(foodGraphicalEllipseItem);
        food.resetFoodSquareGraphicalEllipseItem();
    }
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
