#include "view/game_arena.h"
#include "view/gui_config.h"

GameArena::GameArena(QWidget* parent, Model* model) : QWidget(parent)
{
    model_ = model;
}

void GameArena::paintEvent([[maybe_unused]] QPaintEvent* event)
{
    QPainter painter(this);

    drawGameArena(painter);
    drawSnake(painter);
    drawFood(painter);
}

void GameArena::drawGameArena(QPainter& painter) const
{
    const QPen outlinePen(GuiConfig::GameArenaParameters::WALL_COLOR, GuiConfig::GameArenaParameters::BASIC_SQUARE_SIZE);

    painter.setPen(outlinePen);

    /*Top wall*/
    painter.drawLine(GuiConfig::GameArenaParameters::LEFT_BORDER_X,
                     GuiConfig::GameArenaParameters::TOP_Y,
                     GuiConfig::GameArenaParameters::RIGHT_BORDER_X + GuiConfig::GameArenaParameters::RIGHT_BORDER_X_OFFSET,
                     GuiConfig::GameArenaParameters::TOP_Y);
    /*Left wall*/
    painter.drawLine(GuiConfig::GameArenaParameters::LEFT_BORDER_X,
                     GuiConfig::GameArenaParameters::TOP_Y,
                     GuiConfig::GameArenaParameters::LEFT_BORDER_X,
                     GuiConfig::GameArenaParameters::BOTTOM_Y + GuiConfig::GameArenaParameters::BOTTOM_Y_OFFSET);
    /*Bottom wall*/
    painter.drawLine(GuiConfig::GameArenaParameters::LEFT_BORDER_X,
                     GuiConfig::GameArenaParameters::BOTTOM_Y + GuiConfig::GameArenaParameters::BOTTOM_Y_OFFSET,
                     GuiConfig::GameArenaParameters::RIGHT_BORDER_X + GuiConfig::GameArenaParameters::RIGHT_BORDER_X_OFFSET,
                     GuiConfig::GameArenaParameters::BOTTOM_Y + GuiConfig::GameArenaParameters::BOTTOM_Y_OFFSET);
    /*Right wall*/
    painter.drawLine(GuiConfig::GameArenaParameters::RIGHT_BORDER_X + GuiConfig::GameArenaParameters::RIGHT_BORDER_X_OFFSET,
                     GuiConfig::GameArenaParameters::TOP_Y,
                     GuiConfig::GameArenaParameters::RIGHT_BORDER_X + GuiConfig::GameArenaParameters::RIGHT_BORDER_X_OFFSET,
                     GuiConfig::GameArenaParameters::BOTTOM_Y + GuiConfig::GameArenaParameters::BOTTOM_Y_OFFSET);
}

void GameArena::drawSnake(QPainter& painter) const
{
    painter.setPen(Qt::NoPen);

    Snake* snake = model_->getSnake();

    drawSnakeHead(painter, snake);

    auto& snakeSegments = snake->getSegments();

    for(int i = 1; i < snakeSegments.size(); ++i)
    {
        drawSnakeSegment(painter, snakeSegments.at(i).get());
    }

    drawSnakeEyes(painter, snake);
}

void GameArena::drawSnakeHead(QPainter& painter, Snake* snake) const
{
    const int offsetX_ = 0;
    const int offsetY_ = 0;

    painter.setPen(Qt::NoPen);
    painter.setBrush(GuiConfig::Snake::SNAKE_HEAD_COLOR);

    painter.drawRect(snake->getSegments().at(0)->getCoordinates().x_ * GuiConfig::Snake::SNAKE_SEGMENT_SIZE + offsetX_,
                     snake->getSegments().at(0)->getCoordinates().y_ * GuiConfig::Snake::SNAKE_SEGMENT_SIZE + offsetY_,
                     GuiConfig::Snake::SNAKE_SEGMENT_SIZE,
                     GuiConfig::Snake::SNAKE_SEGMENT_SIZE);
}

void GameArena::drawSnakeSegment(QPainter& painter, SnakeSegment* snakeSegment) const
{
    painter.setPen(Qt::NoPen);
    painter.setBrush(GuiConfig::Snake::SNAKE_BODY_COLOR);

    const Coordinates& coordinates = snakeSegment->getCoordinates();

    painter.drawRect(coordinates.x_ * GuiConfig::Snake::SNAKE_SEGMENT_SIZE,
                     coordinates.y_ * GuiConfig::Snake::SNAKE_SEGMENT_SIZE,
                     GuiConfig::Snake::SNAKE_SEGMENT_SIZE,
                     GuiConfig::Snake::SNAKE_SEGMENT_SIZE);

    if(snakeSegment->isFoodInside())
    {
        drawFoodInsideSnake(painter, snakeSegment);
    }
}

void GameArena::drawFood(QPainter& painter) const
{
    painter.setPen(Qt::NoPen);
    painter.setBrush(GuiConfig::Food::FOOD_COLOR);

    const Coordinates& foodCoordinates = model_->getFood()->getCoordinates();

    painter.drawRect(foodCoordinates.x_ * GuiConfig::GameArenaParameters::BASIC_SQUARE_SIZE + GuiConfig::Food::FOOD_OFFSET,
                     foodCoordinates.y_ * GuiConfig::GameArenaParameters::BASIC_SQUARE_SIZE + GuiConfig::Food::FOOD_OFFSET,
                     GuiConfig::Food::FOOD_SIZE,
                     GuiConfig::Food::FOOD_SIZE);
}

void GameArena::drawFoodInsideSnake(QPainter& painter, SnakeSegment* snakeSegment) const
{
    painter.setPen(Qt::NoPen);
    painter.setBrush(GuiConfig::Food::FOOD_INSIDE_SNAKE_COLOR);

    const Coordinates& coordinates = snakeSegment->getCoordinates();

    painter.drawEllipse(coordinates.x_ * GuiConfig::Snake::SNAKE_SEGMENT_SIZE + GuiConfig::Food::FOOD_INSIDE_SNAKE_OFFSET,
                        coordinates.y_ * GuiConfig::Snake::SNAKE_SEGMENT_SIZE + GuiConfig::Food::FOOD_INSIDE_SNAKE_OFFSET,
                        GuiConfig::Food::FOOD_INSIDE_SNAKE_SIZE,
                        GuiConfig::Food::FOOD_INSIDE_SNAKE_SIZE);
}

void GameArena::drawSnakeEyes(QPainter& painter, Snake* snake) const
{
    auto drawEyes = [&painter, &snake](int eye1XOffset, int eye1YOffset, int eye2XOffset, int eye2YOffset)
    {
        painter.setPen(Qt::NoPen);
        painter.setBrush(GuiConfig::Snake::SNAKE_EYES_COLOR);

        Coordinates snakeHeadCoordinates = snake->getSegments().at(0)->getCoordinates();

        painter.drawEllipse(snakeHeadCoordinates.x_ * GuiConfig::Snake::SNAKE_SEGMENT_SIZE + eye1XOffset,
                            snakeHeadCoordinates.y_ * GuiConfig::Snake::SNAKE_SEGMENT_SIZE + eye1YOffset,
                            GuiConfig::Snake::SNAKE_EYE_SIZE,
                            GuiConfig::Snake::SNAKE_EYE_SIZE);

        painter.drawEllipse(snakeHeadCoordinates.x_ * GuiConfig::Snake::SNAKE_SEGMENT_SIZE + eye2XOffset,
                            snakeHeadCoordinates.y_ * GuiConfig::Snake::SNAKE_SEGMENT_SIZE + eye2YOffset,
                            GuiConfig::Snake::SNAKE_EYE_SIZE,
                            GuiConfig::Snake::SNAKE_EYE_SIZE);
    };

    switch(snake->getDirection())
    {
        case Direction::LEFT:
            drawEyes(5, 5, 5, 20);
            break;

        case Direction::RIGHT:
            drawEyes(20, 5, 20, 20);
            break;

        case Direction::UP:
            drawEyes(5, 5, 20, 5);
            break;

        case Direction::DOWN:
            drawEyes(5, 20, 20, 20);
            break;
    }
}

void GameArena::updateArena()
{
    this->update();
}

[[maybe_unused]] void GameArena::drawAllSquares(QPainter& painter)
{
    static const QBrush redBrush(Qt::red);
    static const QBrush greenBrush(Qt::green);

    painter.setPen(Qt::NoPen);

    for(int column = 0; column < Config::Arena::COLUMNS_COUNT; column++)
    {
        for(int row = 0; row < Config::Arena::ROWS_COUNT; row++)
        {
            /*Even columns*/
            if(column % 2 == 0)
            {
                if(row % 2 == 0)
                {
                    painter.setBrush(redBrush);

                    painter.drawRect(column * GuiConfig::Snake::SNAKE_SEGMENT_SIZE + GuiConfig::Snake::SNAKE_SEGMENT_SIZE,
                                     row * GuiConfig::Snake::SNAKE_SEGMENT_SIZE + GuiConfig::Snake::SNAKE_SEGMENT_SIZE,
                                     GuiConfig::Snake::SNAKE_SEGMENT_SIZE,
                                     GuiConfig::Snake::SNAKE_SEGMENT_SIZE);
                }
                else
                {
                    painter.setBrush(greenBrush);

                    painter.drawRect(column * GuiConfig::Snake::SNAKE_SEGMENT_SIZE + GuiConfig::Snake::SNAKE_SEGMENT_SIZE,
                                     row * GuiConfig::Snake::SNAKE_SEGMENT_SIZE + GuiConfig::Snake::SNAKE_SEGMENT_SIZE,
                                     GuiConfig::Snake::SNAKE_SEGMENT_SIZE,
                                     GuiConfig::Snake::SNAKE_SEGMENT_SIZE);
                }
            }
                /*Odd columns*/
            else
            {
                if(row % 2 == 0)
                {
                    painter.setBrush(greenBrush);

                    painter.drawRect(column * GuiConfig::Snake::SNAKE_SEGMENT_SIZE + GuiConfig::Snake::SNAKE_SEGMENT_SIZE,
                                     row * GuiConfig::Snake::SNAKE_SEGMENT_SIZE + GuiConfig::Snake::SNAKE_SEGMENT_SIZE,
                                     GuiConfig::Snake::SNAKE_SEGMENT_SIZE,
                                     GuiConfig::Snake::SNAKE_SEGMENT_SIZE);
                }
                else
                {
                    painter.setBrush(redBrush);

                    painter.drawRect(column * GuiConfig::Snake::SNAKE_SEGMENT_SIZE + GuiConfig::Snake::SNAKE_SEGMENT_SIZE,
                                     row * GuiConfig::Snake::SNAKE_SEGMENT_SIZE + GuiConfig::Snake::SNAKE_SEGMENT_SIZE,
                                     GuiConfig::Snake::SNAKE_SEGMENT_SIZE,
                                     GuiConfig::Snake::SNAKE_SEGMENT_SIZE);
                }
            }
        }
    }
}
