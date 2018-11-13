#pragma once

#include <cstdlib>

class IdGenerator
{
public:
    static uint generateId()
    {
        return ++currentId_;
    }

private:
    inline static uint currentId_;
};
