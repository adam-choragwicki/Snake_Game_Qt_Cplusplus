#include "game_arena.h"
#include "gui_config.h"

using namespace Config::Arena;
using namespace GuiConfig::GameArena;

GameArena::GameArena(QWidget* parent, const Model& model) : QWidget(parent), model_(model)
{}

void GameArena::paintEvent([[maybe_unused]] QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    drawGameArena(painter);

    drawSnake(painter, model_.getSnake());

    if(model_.getFoodManager().foodExists())
    {
        drawFood(painter, model_.getFoodManager().getFood());
    }
}

void GameArena::drawGameArena(QPainter& painter) const
{
    painter.setPen(Qt::NoPen);
    painter.setBrush(Edge::COLOR);

    auto drawEdgeBlock = [&painter](int x, int y)
    {
        painter.drawRect(x * Field::SIZE, y * Field::SIZE, Field::SIZE, Field::SIZE);
    };

    auto drawLeftEdge = [&drawEdgeBlock](QPainter& painter)
    {
        for(int y = MINIMUM_Y; y <= MAXIMUM_Y; ++y)
        {
            drawEdgeBlock(MINIMUM_X - 1, y);
        }
    };

    auto drawRightEdge = [&drawEdgeBlock](QPainter& painter)
    {
        for(int y = MINIMUM_Y; y <= MAXIMUM_Y; ++y)
        {
            drawEdgeBlock(MAXIMUM_X + 1, y);
        }
    };

    auto drawTopEdge = [&drawEdgeBlock](QPainter& painter)
    {
        for(int x = MINIMUM_X; x <= MAXIMUM_X; ++x)
        {
            drawEdgeBlock(x, MINIMUM_Y - 1);
        }
    };

    auto drawBottomEdge = [&drawEdgeBlock](QPainter& painter)
    {
        for(int x = MINIMUM_Y; x <= MAXIMUM_X; ++x)
        {
            drawEdgeBlock(x, MAXIMUM_Y + 1);
        }
    };

    auto drawCorners = [&drawEdgeBlock](QPainter& painter)
    {
        drawEdgeBlock(MINIMUM_X - 1, MINIMUM_Y - 1);
        drawEdgeBlock(MAXIMUM_X + 1, MINIMUM_Y - 1);
        drawEdgeBlock(MINIMUM_X - 1, MAXIMUM_Y + 1);
        drawEdgeBlock(MAXIMUM_X + 1, MAXIMUM_Y + 1);
    };

    drawLeftEdge(painter);
    drawRightEdge(painter);
    drawTopEdge(painter);
    drawBottomEdge(painter);
    drawCorners(painter);
}

void GameArena::drawSnakeSegment(QPainter& painter, const Coordinates& coordinates) const
{
    painter.setPen(Qt::NoPen);
    painter.setBrush(GuiConfig::Snake::BODY_COLOR);

    painter.drawRoundedRect(coordinates.x_ * GuiConfig::Snake::SEGMENT_SIZE,
                            coordinates.y_ * GuiConfig::Snake::SEGMENT_SIZE,
                            GuiConfig::Snake::SEGMENT_SIZE,
                            GuiConfig::Snake::SEGMENT_SIZE,
                            GuiConfig::Snake::ROUNDED_RECT_RATIO_PERCENTAGE,
                            GuiConfig::Snake::ROUNDED_RECT_RATIO_PERCENTAGE,
                            Qt::RelativeSize);
}

void GameArena::drawSnake(QPainter& painter, const Snake& snake) const
{
    painter.setPen(Qt::NoPen);

    drawSnakeHead(painter, snake);

    for(int i = 1; i < snake.length(); ++i)
    {
        drawSnakeSegment(painter, snake.getSegmentAt(i).getCoordinates());
    }
}

void GameArena::drawSnakeHead(QPainter& painter, const Snake& snake) const
{
    painter.setPen(Qt::NoPen);
    painter.setBrush(GuiConfig::Snake::HEAD_COLOR);

    painter.drawRoundedRect(snake.getHeadCoordinates().x_ * GuiConfig::Snake::SEGMENT_SIZE,
                            snake.getHeadCoordinates().y_ * GuiConfig::Snake::SEGMENT_SIZE,
                            GuiConfig::Snake::SEGMENT_SIZE,
                            GuiConfig::Snake::SEGMENT_SIZE,
                            GuiConfig::Snake::ROUNDED_RECT_RATIO_PERCENTAGE,
                            GuiConfig::Snake::ROUNDED_RECT_RATIO_PERCENTAGE,
                            Qt::RelativeSize);

    drawSnakeEyes(painter, snake);
}

void GameArena::drawFood(QPainter& painter, const Food& food) const
{
    painter.setPen(Qt::NoPen);
    painter.setBrush(GuiConfig::Food::COLOR);

    const Coordinates& foodCoordinates = food.getCoordinates();

    painter.drawEllipse(foodCoordinates.x_ * Field::SIZE + GuiConfig::Food::OFFSET, foodCoordinates.y_ * Field::SIZE + GuiConfig::Food::OFFSET, GuiConfig::Food::SIZE, GuiConfig::Food::SIZE);
}

void GameArena::drawSnakeEyes(QPainter& painter, const Snake& snake) const
{
    auto drawEyes = [&painter, &snake](int eye1XOffset, int eye1YOffset, int eye2XOffset, int eye2YOffset)
    {
        painter.setPen(Qt::NoPen);
        painter.setBrush(GuiConfig::Snake::EYES_COLOR);

        Coordinates snakeHeadCoordinates = snake.getHeadCoordinates();

        painter.drawEllipse(snakeHeadCoordinates.x_ * GuiConfig::Snake::SEGMENT_SIZE + eye1XOffset, snakeHeadCoordinates.y_ * GuiConfig::Snake::SEGMENT_SIZE + eye1YOffset, GuiConfig::Snake::EYE_SIZE, GuiConfig::Snake::EYE_SIZE);

        painter.drawEllipse(snakeHeadCoordinates.x_ * GuiConfig::Snake::SEGMENT_SIZE + eye2XOffset, snakeHeadCoordinates.y_ * GuiConfig::Snake::SEGMENT_SIZE + eye2YOffset, GuiConfig::Snake::EYE_SIZE, GuiConfig::Snake::EYE_SIZE);
    };

    switch(snake.getMovementDirection())
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

[[maybe_unused]] void GameArena::drawAllPossibleSquares(QPainter& painter)
{
    for(int x = MINIMUM_X; x <= MAXIMUM_X; ++x)
    {
        for(int y = MINIMUM_Y; y <= MAXIMUM_Y; ++y)
        {
            drawSnakeSegment(painter, Coordinates{x, y});
        }
    }
}
