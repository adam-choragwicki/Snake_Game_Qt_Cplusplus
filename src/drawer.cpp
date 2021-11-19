#include "drawer.h"
#include "common.h"
#include <QDebug>

QGraphicsScene* Drawer::scene_ = nullptr;

void Drawer::drawSnake(const QVector<QPoint>& snakeSquarePositions, QVector<QGraphicsRectItem*>& snakeSquaresGraphicalRectItems)
{
    QPen redPen(Qt::red);
    QBrush yellowBrush(Qt::yellow);
    QBrush greenBrush(Qt::green);

    for(auto& snakeSquarePosition : snakeSquarePositions)
    {
        snakeSquaresGraphicalRectItems.append(scene_->addRect(snakeSquarePosition.x() * gameArenaParameters::SQUARE_SIZE  + gameArenaParameters::SQUARE_SIZE,
                                                              snakeSquarePosition.y() * gameArenaParameters::SQUARE_SIZE  + gameArenaParameters::SQUARE_SIZE,
                                                              gameArenaParameters::SQUARE_SIZE,
                                                              gameArenaParameters::SQUARE_SIZE,
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

QGraphicsRectItem* Drawer::drawFood(QPoint foodPosition)
{
    QPen redPen(Qt::red);
    QBrush redBrush(Qt::red);

    QGraphicsRectItem* pFoodSquareGraphicalRectItem = scene_->addRect(foodPosition.x() * gameArenaParameters::SQUARE_SIZE + gameArenaParameters::SQUARE_SIZE,
                                                                      foodPosition.y() * gameArenaParameters::SQUARE_SIZE + gameArenaParameters::SQUARE_SIZE,
                                                                      gameArenaParameters::SQUARE_SIZE,
                                                                      gameArenaParameters::SQUARE_SIZE,
                                                                      redPen,
                                                                      redBrush);

    return pFoodSquareGraphicalRectItem;
}

void Drawer::eraseFood(QGraphicsRectItem* pFoodSquareGraphicalRectItem)
{
    scene_->removeItem(pFoodSquareGraphicalRectItem);
}

void Drawer::drawAllSquares()
{
    QBrush redBrush(Qt::red);
    QBrush greenBrush(Qt::green);

    for(int column = 0 ; column < gameArenaParameters::COLUMNS_COUNT; column++)
    {
        for(int row = 0; row < gameArenaParameters::ROWS_COUNT; row++)
        {
            /*Even columns*/
            if(column % 2 == 0)
            {
                if(row % 2 == 0)
                {
                    scene_->addRect(column * gameArenaParameters::SQUARE_SIZE + gameArenaParameters::SQUARE_SIZE,
                                    row * gameArenaParameters::SQUARE_SIZE + gameArenaParameters::SQUARE_SIZE,
                                    gameArenaParameters::SQUARE_SIZE,
                                    gameArenaParameters::SQUARE_SIZE,
                                    Qt::NoPen,
                                    redBrush);
                }
                else
                {
                    scene_->addRect(column * gameArenaParameters::SQUARE_SIZE + gameArenaParameters::SQUARE_SIZE,
                                    row * gameArenaParameters::SQUARE_SIZE + gameArenaParameters::SQUARE_SIZE,
                                    gameArenaParameters::SQUARE_SIZE,
                                    gameArenaParameters::SQUARE_SIZE,
                                    Qt::NoPen,
                                    greenBrush);
                }
            }
            /*Odd columns*/
            else
            {
                if(row % 2 == 0)
                {
                    scene_->addRect(column * gameArenaParameters::SQUARE_SIZE + gameArenaParameters::SQUARE_SIZE,
                                    row * gameArenaParameters::SQUARE_SIZE + gameArenaParameters::SQUARE_SIZE,
                                    gameArenaParameters::SQUARE_SIZE,
                                    gameArenaParameters::SQUARE_SIZE,
                                    Qt::NoPen,
                                    greenBrush);
                }
                else
                {
                    scene_->addRect(column * gameArenaParameters::SQUARE_SIZE + gameArenaParameters::SQUARE_SIZE,
                                    row * gameArenaParameters::SQUARE_SIZE + gameArenaParameters::SQUARE_SIZE,
                                    gameArenaParameters::SQUARE_SIZE,
                                    gameArenaParameters::SQUARE_SIZE,
                                    Qt::NoPen,
                                    redBrush);
                }
            }
        }
    }
}

void Drawer::drawGameArena()
{
    QPen pen(Qt::white, gameArenaParameters::SQUARE_SIZE);

    /*Top wall*/
    scene_->addLine(gameArenaParameters::LEFT_BORDER_X,
                    gameArenaParameters::TOP_Y,
                    gameArenaParameters::RIGHT_BORDER_X + gameArenaParameters::RIGHT_BORDER_X_OFFSET,
                    gameArenaParameters::TOP_Y,
                    pen);
    /*Left wall*/
    scene_->addLine(gameArenaParameters::LEFT_BORDER_X,
                    gameArenaParameters::TOP_Y,
                    gameArenaParameters::LEFT_BORDER_X,
                    gameArenaParameters::BOTTOM_Y + gameArenaParameters::BOTTOM_Y_OFFSET,
                    pen);
    /*Bottom wall*/
    scene_->addLine(gameArenaParameters::LEFT_BORDER_X,
                    gameArenaParameters::BOTTOM_Y + gameArenaParameters::BOTTOM_Y_OFFSET,
                    gameArenaParameters::RIGHT_BORDER_X + gameArenaParameters::RIGHT_BORDER_X_OFFSET,
                    gameArenaParameters::BOTTOM_Y + gameArenaParameters::BOTTOM_Y_OFFSET,
                    pen);
    /*Right wall*/
    scene_->addLine(gameArenaParameters::RIGHT_BORDER_X + gameArenaParameters::RIGHT_BORDER_X_OFFSET,
                    gameArenaParameters::TOP_Y,
                    gameArenaParameters::RIGHT_BORDER_X + gameArenaParameters::RIGHT_BORDER_X_OFFSET,
                    gameArenaParameters::BOTTOM_Y + gameArenaParameters::BOTTOM_Y_OFFSET,
                    pen);
}
