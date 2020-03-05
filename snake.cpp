#include "snake.h"

Snake::Snake()
{
    m_Positions = m_StartingPositions;
    m_HeadPosition = m_Positions.front();

    SetDirection(Direction::right);
    SetNextDirection(Direction::right);
}

void Snake::Move()
{
    switch(m_Direction)
    {
    case Direction::left:
        m_Positions.removeLast(); //delete last element
        m_Positions.prepend(QPoint(m_HeadPosition.x() - 1, m_HeadPosition.y()));
        SetHeadPosition(QPoint(m_Positions.front()));
        break;
    case Direction::up:
        m_Positions.removeLast(); //delete last element
        m_Positions.prepend(QPoint(m_HeadPosition.x(), m_HeadPosition.y() - 1));
        SetHeadPosition(QPoint(m_Positions.front()));
        break;
    case Direction::down:
        m_Positions.removeLast(); //delete last element
        m_Positions.prepend(QPoint(m_HeadPosition.x(), m_HeadPosition.y() + 1));
        SetHeadPosition(QPoint(m_Positions.front()));
        break;
    case Direction::right:
        m_Positions.removeLast(); //delete last element
        m_Positions.prepend(QPoint(m_HeadPosition.x() + 1, m_HeadPosition.y()));
        SetHeadPosition(QPoint(m_Positions.front()));
        break;
    default:
        assert(false);
    }
}

void Snake::Grow()
{
    switch(m_Direction)
    {
    case Direction::left:
        m_Positions.prepend(QPoint(m_HeadPosition.x() - 1, m_HeadPosition.y()));
        SetHeadPosition(QPoint(m_Positions.front()));
        break;
    case Direction::up:
        m_Positions.prepend(QPoint(m_HeadPosition.x(), m_HeadPosition.y() - 1));
        SetHeadPosition(QPoint(m_Positions.front()));
        break;
    case Direction::down:
        m_Positions.prepend(QPoint(m_HeadPosition.x(), m_HeadPosition.y() + 1));
        SetHeadPosition(QPoint(m_Positions.front()));
        break;
    case Direction::right:
        m_Positions.prepend(QPoint(m_HeadPosition.x() + 1, m_HeadPosition.y()));
        SetHeadPosition(QPoint(m_Positions.front()));
        break;
    default:
        assert(false);
    }
}

void Snake::Reset()
{
    m_Positions.clear();
    m_Positions.squeeze();

    m_Positions = m_StartingPositions;
    m_HeadPosition = m_Positions.front();

    SetDirection(Direction::right);
    SetNextDirection(Direction::right);
}
