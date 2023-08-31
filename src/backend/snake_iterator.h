#pragma once

#include "model/snake.h"

class SnakeReverseIterator
{
public:
    explicit SnakeReverseIterator(std::vector<SnakeSegment>& segments);
    bool hasNext();
    bool isDone();
    void advance();
    SnakeSegment& current();
    SnakeSegment& next();

private:
    std::vector<SnakeSegment>& segments_;
    std::vector<SnakeSegment>::reverse_iterator currentIter_;
};
