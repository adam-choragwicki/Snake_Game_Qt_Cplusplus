#pragma once

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QVector>
#include <QPoint>

class Drawer
{
public:
    Drawer(QGraphicsScene* pScene);
    void DrawSnake(QVector<QPoint> positions);
    void EraseSnake();
    void DrawFood(QPoint foodPosition);
    void EraseFood();

private:
    QGraphicsScene* m_pScene;
    QVector<QGraphicsRectItem*> m_DrawnItems;
    QGraphicsRectItem* m_pDrawnFood;
};
