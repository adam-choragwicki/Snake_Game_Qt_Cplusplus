#include "snake_iterator.h"

SnakeReverseIterator::SnakeReverseIterator(std::vector<SnakeSegment>& segments) : segments_(segments)
{
    currentIter_ = segments_.rbegin();
}

bool SnakeReverseIterator::hasNext()
{
    return (currentIter_ != segments_.rend()) && ((currentIter_ + 1) != segments_.rend());
}

bool SnakeReverseIterator::isDone()
{
    return currentIter_ == segments_.rend();
}

void SnakeReverseIterator::advance()
{
    ++currentIter_;
}

SnakeSegment& SnakeReverseIterator::current()
{
    return *currentIter_;
}

SnakeSegment& SnakeReverseIterator::next()
{
    if(hasNext())
    {
        return *(currentIter_ + 1);
    }
    else
    {
        throw std::runtime_error("Error, called next() on iterator pointing to the last element");
    }
}
