#pragma once

#include "body_segment.h"

class HeadSegment : public BodySegment
{
public:
    HeadSegment(const Coordinates& coordinates, const Direction& movementDirection);
    ~HeadSegment() override = default;
};
