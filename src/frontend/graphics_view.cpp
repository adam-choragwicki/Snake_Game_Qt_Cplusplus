#include "graphics_view.h"
#include "model/graphics_scene.h"
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>

GraphicsView::GraphicsView(GraphicsScene* scene, QWidget* parent) : QGraphicsView(scene, parent)
{
    setFocusPolicy(Qt::NoFocus);
    setViewportUpdateMode(QGraphicsView::NoViewportUpdate);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHint(QPainter::Antialiasing, true);

    connect(&fpsTimer_, &QTimer::timeout, this, &GraphicsView::updateFPS);

    /* Update FPS every 500m */
    fpsTimer_.start(500);
    frameTimeTimer_.start();

    initializePainterData();

    viewport()->installEventFilter(this);
}

void GraphicsView::drawForeground(QPainter* painter, const QRectF& rect)
{
    /* Ensure FPS counter is drawn on top of scene and always visible */
    QGraphicsView::drawForeground(painter, rect);

    ++frameCount_;

    painter->setPen(fpsCounterPen_);
    painter->setFont(fpsCounterFont_);

    const QPointF topLeft = mapToScene(viewport()->rect().topLeft());
    painter->drawText(topLeft + QPointF(10, 20), QString("FPS: %1").arg(qRound(currentFPS_)));
}

void GraphicsView::updateFPS()
{
    qint64 elapsed = frameTimeTimer_.elapsed();
    currentFPS_ = (frameCount_ * 1000.0) / elapsed;
    frameCount_ = 0;
    frameTimeTimer_.restart();
}

bool GraphicsView::eventFilter(QObject* obj, QEvent* event)
{
    if(event->type() == QEvent::Wheel)
    {
        /* Ignore mouse wheel events to disable scene scrolling */
        return true;
    }

    return QGraphicsView::eventFilter(obj, event);
}

void GraphicsView::initializePainterData()
{
    fpsCounterFont_.setFamily("Arial");
    fpsCounterFont_.setPointSize(20);
    fpsCounterFont_.setBold(true);

    fpsCounterPen_.setColor(Qt::red);
}

void GraphicsView::updateViewport()
{
    viewport()->update();
}
