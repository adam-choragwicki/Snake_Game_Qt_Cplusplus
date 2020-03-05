#include "snake.h"

Snake::Snake()
{
    Initialize();
}

void Snake::Initialize()
{
    m_Positions.append(QPoint(25,12));
    m_Positions.append(QPoint(24,12));
    m_Positions.append(QPoint(23,12));

    /*Initial head position X*/
    m_HeadPosition.setX(m_Positions.front().x());
    /*Initial head position Y*/
    m_HeadPosition.setY(m_Positions.front().y());

    SetDirection(right);
    SetNextDirection(right);
}

void Snake::Move()
{
    switch(m_Direction)
    {
    case left:
        m_Positions.removeLast(); //delete last element
        m_Positions.prepend(QPoint(m_HeadPosition.x() - 1, m_HeadPosition.y()));
        SetHeadPosition(QPoint(m_Positions.front()));
        break;
    case up:
        m_Positions.removeLast(); //delete last element
        m_Positions.prepend(QPoint(m_HeadPosition.x(), m_HeadPosition.y() - 1));
        SetHeadPosition(QPoint(m_Positions.front()));
        break;
    case down:
        m_Positions.removeLast(); //delete last element
        m_Positions.prepend(QPoint(m_HeadPosition.x(), m_HeadPosition.y() + 1));
        SetHeadPosition(QPoint(m_Positions.front()));
        break;
    case right:
        m_Positions.removeLast(); //delete last element
        m_Positions.prepend(QPoint(m_HeadPosition.x() + 1, m_HeadPosition.y()));
        SetHeadPosition(QPoint(m_Positions.front()));
        break;
    default:
        qDebug() << "Wrong m_Direction in Snake::move(int m_Direction)";
    }
}

void Snake::Grow()
{
    switch(m_Direction)
    {
    case left:
        m_Positions.prepend(QPoint(m_HeadPosition.x() - 1, m_HeadPosition.y()));
        SetHeadPosition(QPoint(m_Positions.front()));
        break;
    case up:
        m_Positions.prepend(QPoint(m_HeadPosition.x(), m_HeadPosition.y() - 1));
        SetHeadPosition(QPoint(m_Positions.front()));
        break;
    case down:
        m_Positions.prepend(QPoint(m_HeadPosition.x(), m_HeadPosition.y() + 1));
        SetHeadPosition(QPoint(m_Positions.front()));
        break;
    case right:
        m_Positions.prepend(QPoint(m_HeadPosition.x() + 1, m_HeadPosition.y()));
        SetHeadPosition(QPoint(m_Positions.front()));
        break;
    default:
        qDebug() << "Wrong m_Direction in Snake::grow(int m_Direction)";
    }
}

//used to restart game
void Snake::ClearPositions()
{
    m_Positions.clear();
    m_Positions.squeeze();
}
