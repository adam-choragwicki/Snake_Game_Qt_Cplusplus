#pragma once

#include "direction.h"
#include "coordinates.h"
#include "body_segment.h"
#include <vector>
#include "config_prod.h"
#include "animation_manager.h"
#include <QObject>

class HeadSegment;
class SnakeReverseIterator;

class Snake : public QObject
{
Q_OBJECT

    friend std::ostream& operator<<(std::ostream& os, const Snake& snake);

signals:
    void segmentAdded(BodySegment& snakeSegment);

public:
    explicit Snake(const Coordinates& startingHeadCoordinates, Direction startingDirection, int startingTotalSegmentsCount, AnimationManager* animationManager);

    ~Snake() override = default;

    void reset();

    void moveForward();
    void eatFood();

    void setNextHeadDirection(const Direction& nextDirection);

    [[nodiscard]] BodySegment& getSegmentAt(size_t index)
    { return *segments_.at(index); }

    [[nodiscard]] std::vector<Coordinates> getAllSegmentsCoordinates() const;

    [[nodiscard]] std::vector<Coordinates> getAllSegmentsCoordinatesExceptForHead() const;

    [[nodiscard]] const HeadSegment& getHead() const;

    [[nodiscard]] HeadSegment& getHead();

    [[nodiscard]] Coordinates getHeadCoordinates() const;

    [[nodiscard]] Direction getMovementDirection() const;

    [[nodiscard]] const BodySegment& getTail() const
    { return *segments_.back(); }

    [[nodiscard]] BodySegment& getTail()
    { return *segments_.back(); }

    [[nodiscard]] Coordinates getTailCoordinates() const
    { return getTail().getCoordinates(); }

    [[nodiscard]] size_t length() const
    { return segments_.size(); };

    SnakeReverseIterator createReverseIterator();

    [[nodiscard]] const std::vector<std::unique_ptr<BodySegment>>& getSegments() const
    { return segments_; }

    void grow();

    [[nodiscard]] bool isSupposedToGrow() const
    { return growFlag_; }

    bool isNewMovementDirectionRequested();
    void updateMovementDirection();

    void setNewFoodPosition(const QPointF& foodPosition);

    QString toString() const;

private:
    void createHead();
    void createSegments();
    void appendSegment();

    const Coordinates STARTING_HEAD_COORDINATES;
    const Direction STARTING_DIRECTION;
    const int STARTING_TOTAL_SEGMENT_COUNT;

    Direction nextHeadDirection_;
    std::vector<std::unique_ptr<BodySegment>> segments_;

    AnimationManager* animationManager_{};

    bool growFlag_{};
};
