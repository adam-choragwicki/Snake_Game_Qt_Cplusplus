#pragma once

#include <QGraphicsView>
#include <QTimer>
#include <QElapsedTimer>

class QTimer;
class GraphicsScene;

class GraphicsView : public QGraphicsView
{
Q_OBJECT

public:
    explicit GraphicsView(GraphicsScene* scene, QWidget* parent = nullptr);

    void drawForeground(QPainter* painter, const QRectF& rect) override;
    bool eventFilter(QObject* obj, QEvent* event) override;

    void updateViewport();

private slots:
    void updateFPS();

private:
    void initializePainterData();

    QTimer fpsTimer_;
    QElapsedTimer frameTimeTimer_;
    int frameCount_{};
    double currentFPS_{};

    QFont fpsCounterFont_;
    QPen fpsCounterPen_;
};
