#pragma once

#include "direction.h"
#include "coordinates.h"
#include "snake_segment.h"
#include <vector>
#include "log_manager.h"
#include "config.h"
#include <QObject>

class SnakeReverseIterator;

class Snake : public QObject
{
Q_OBJECT

    friend std::ostream& operator<<(std::ostream& os, const Snake& snake);

public:
    Snake();
    ~Snake() override = default;

    void moveForward();
    void eatFood();

    void setNextHeadDirection(const Direction& nextDirection);

    [[nodiscard]] const SnakeSegment& getSegmentAt(size_t index) const
    { return segments_.at(index); }

    [[nodiscard]] SnakeSegment& getSegmentAt(size_t index)
    { return segments_.at(index); }

    [[nodiscard]] std::vector<Coordinates> getAllSegmentsCoordinates() const;

    [[nodiscard]] std::vector<Coordinates> getAllSegmentsCoordinatesExceptForHead() const;

    [[nodiscard]] const SnakeSegment& getHead() const
    { return segments_.front(); }

    [[nodiscard]] SnakeSegment& getHead()
    { return segments_.front(); }

    [[nodiscard]] Coordinates getHeadCoordinates() const
    { return getHead().getCoordinates(); }

    [[nodiscard]] Direction getMovementDirection() const
    { return getHead().getMovementDirection(); }

    [[nodiscard]] const SnakeSegment& getTail() const
    { return segments_.back(); }

    [[nodiscard]] SnakeSegment& getTail()
    { return segments_.back(); }

    [[nodiscard]] Coordinates getTailCoordinates() const
    { return getTail().getCoordinates(); }

    [[nodiscard]] size_t length() const
    { return segments_.size(); };

    SnakeReverseIterator createIterator();

    bool growFlag_{};

private:
    Direction nextHeadDirection_;
    std::vector<SnakeSegment> segments_;

    void createHead();
    void appendSegment();
};
