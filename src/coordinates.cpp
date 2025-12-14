#include "coordinates.h"

Coordinates::Coordinates(const int x, const int y) : x_(x), y_(y)
{}

bool operator==(const Coordinates& coordinates1, const Coordinates& coordinates2)
{
    return coordinates1.x_ == coordinates2.x_ && coordinates1.y_ == coordinates2.y_;
}

bool operator!=(const Coordinates& coordinates1, const Coordinates& coordinates2)
{
    return !(coordinates1 == coordinates2);
}

bool operator<(const Coordinates& coordinates1, const Coordinates& coordinates2)
{
    if(coordinates1.x_ < coordinates2.x_)
    {
        return true;
    }

    if(coordinates1.x_ > coordinates2.x_)
    {
        return false;
    }

    return coordinates1.y_ < coordinates2.y_;
}

Coordinates& Coordinates::operator+=(const Coordinates& coordinates)
{
    x_ += coordinates.x_;
    y_ += coordinates.y_;

    return *this;
}

Coordinates Coordinates::operator+(const std::pair<int, int>& coordinates) const
{
    return {x_ + coordinates.first, y_ + coordinates.second};
}

std::pair<int, int> Coordinates::operator-(const Coordinates& coordinates) const
{
    return {x_ - coordinates.x_, y_ - coordinates.y_};
}

std::ostream& operator<<(std::ostream& os, const Coordinates& coordinates)
{
    os << "[" << coordinates.x_ << "," << coordinates.y_ << "]";
    return os;
}

QString Coordinates::toString() const
{
    return {("[" + QString::number(x_) + "," + QString::number(y_) + "]")};
}
