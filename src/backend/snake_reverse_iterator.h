#pragma once

#include "model/snake.h"

class SnakeReverseIterator
{
public:
    explicit SnakeReverseIterator(std::vector<std::unique_ptr<BodySegment>>& segments);
    bool hasNext();
    bool isDone();
    void advance();
    BodySegment& current();
    BodySegment& next();

private:
    std::vector<std::unique_ptr<BodySegment>>& segments_;
    std::vector<std::unique_ptr<BodySegment>>::reverse_iterator currentIter_;
};
