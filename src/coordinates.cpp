#include "coordinates.h"

bool operator==(const Coordinates& coordinates1, const Coordinates& coordinates2)
{
    return (coordinates1.x == coordinates2.x) && (coordinates1.y == coordinates2.y);
}

bool operator!=(const Coordinates& coordinates1, const Coordinates& coordinates2)
{
    return !(coordinates1 == coordinates2);
}

bool operator<(const Coordinates& coordinates1, const Coordinates& coordinates2)
{
    if(coordinates1.x < coordinates2.x)
    {
        return true;
    }
    else if(coordinates1.x > coordinates2.x)
    {
        return false;
    }
    else
    {
        return coordinates1.y < coordinates2.y;
    }
}
