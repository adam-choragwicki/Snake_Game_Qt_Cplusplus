#pragma once

#include "qml_helper.h"

class OverlayManager
{
public:
    explicit OverlayManager(QmlHelper& qml_helper);

    void showStartingImageOverlay();
    void hideStartingImageOverlay();

    void showEscapeMenuOverlay();
    void hideEscapeMenuOverlay();

    void showEndGameOverlay(const QString& score);
    void hideEndGameOverlay();

private:
    QmlHelper& qmlHelper_;

    QObject* startingImageOverlay_{};
    QObject* escapeMenuOverlay_{};
    QObject* endGameOverlay_{};
};
