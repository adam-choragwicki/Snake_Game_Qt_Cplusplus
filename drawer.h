#pragma once

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QVector>
#include <QPoint>

class Drawer
{
public:
    Drawer() = delete;
    Drawer(Drawer const&) = delete;
    Drawer& operator=(Drawer&) = delete;
    Drawer(Drawer const&&) = delete;
    Drawer& operator=(Drawer&&) = delete;

    static void SetScene(QGraphicsScene* pScene) {m_pScene = pScene;}
    static void DrawSnake(QVector<QPoint> positions);
    static void EraseSnake();
    static void DrawFood(QPoint foodPosition);
    static void EraseFood();

private:
    static QGraphicsScene* m_pScene;
    static QVector<QGraphicsRectItem*> m_DrawnItems;
    static QGraphicsRectItem* m_pDrawnFood;
};
