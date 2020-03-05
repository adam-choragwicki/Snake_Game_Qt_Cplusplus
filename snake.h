#pragma once

#include <QObject>
#include <QVector>
#include <QPoint>
#include <QDebug>

class Snake
{
public:
    Snake();
    void Initialize();
    void Move();
    bool IsMovePossible();
    void Grow();

    void ClearPositions();

    void SetHeadPosition(QPoint headPosition) {m_HeadPosition = headPosition;}
    void SetDirection(int direction) {m_Direction = direction;}
    void SetNextDirection(int nextDirection) {m_NextDirection = nextDirection;}

    QVector<QPoint> GetPositions() {return m_Positions;}
    QPoint GetHeadPosition() {return m_HeadPosition;}
    QPoint GetTailPosition() {return m_TailPosition;}
    int GetDirection() {return m_Direction;}
    int GetNextDirection() {return m_NextDirection;}

    enum direction {left = 1, up = 2, down = 3, right = 4};

private:
    int m_Size;
    int m_Direction;
    int m_NextDirection;
    QPoint m_HeadPosition;
    QPoint m_TailPosition;
    QVector<QPoint> m_Positions;
    bool m_IsGrowing;
};
