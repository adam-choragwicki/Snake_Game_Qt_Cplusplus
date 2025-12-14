#pragma once

#include "direction.h"
#include "coordinates.h"
#include "body_segment.h"
#include <vector>
#include "game_config.h"
#include <QObject>

class HeadSegment;

class Snake : public QObject
{
Q_OBJECT

    friend std::ostream& operator<<(std::ostream& os, const Snake& snake);

signals:
    void stateChanged();

public:
    explicit Snake(const GameConfig& gameConfig, const Coordinates& startingHeadCoordinates, Direction startingDirection, int startingTotalSegmentsCount);

    ~Snake() override = default;

    void reset();

    void moveForward();

    void eatFood();

    void setNextHeadDirection(const Direction& nextDirection);

    [[nodiscard]] BodySegment& getSegmentAt(const size_t index) const { return *segments_.at(index); }

    [[nodiscard]] std::vector<Coordinates> getAllSegmentsCoordinates() const;

    [[nodiscard]] std::vector<Coordinates> getAllSegmentsCoordinatesExceptForHead() const;

    [[nodiscard]] const HeadSegment& getHead() const;

    [[nodiscard]] HeadSegment& getHead();

    [[nodiscard]] Coordinates getHeadCoordinates() const;

    [[nodiscard]] Direction getMovementDirection() const;

    [[nodiscard]] const BodySegment& getTail() const { return *segments_.back(); }

    [[nodiscard]] BodySegment& getTail() { return *segments_.back(); }

    [[nodiscard]] Coordinates getTailCoordinates() const { return getTail().getCoordinates(); }

    [[nodiscard]] size_t length() const { return segments_.size(); }

    [[nodiscard]] const std::vector<std::unique_ptr<BodySegment>>& getSegments() const { return segments_; }

    void grow();

    [[nodiscard]] bool isSupposedToGrow() const { return growFlag_; }

    bool isNewMovementDirectionRequested();
    void updateMovementDirection();

    [[nodiscard]] QString toString() const;

private:
    void createHead();
    void createSegments();
    void appendSegment();

    void moveBodySegments();
    void moveHead();

    const Coordinates STARTING_HEAD_COORDINATES;
    const Direction STARTING_DIRECTION;
    const int STARTING_TOTAL_SEGMENT_COUNT;

    Direction nextHeadDirection_;
    std::vector<std::unique_ptr<BodySegment>> segments_;

    bool growFlag_{};
};
