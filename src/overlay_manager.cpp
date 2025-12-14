#include "overlay_manager.h"

OverlayManager::OverlayManager(QmlHelper& qml_helper) : qmlHelper_(qml_helper)
{
    startingImageOverlay_ = qmlHelper_.getOverlay(QmlOverlay::StartingImageOverlay);
    escapeMenuOverlay_ = qmlHelper_.getOverlay(QmlOverlay::EscapeMenuOverlay);
    endGameOverlay_ = qmlHelper_.getOverlay(QmlOverlay::EndGameOverlay);
}

void OverlayManager::showStartingImageOverlay()
{
    startingImageOverlay_->setProperty("visible", true);
}

void OverlayManager::hideStartingImageOverlay()
{
    startingImageOverlay_->setProperty("visible", false);
}

void OverlayManager::showEscapeMenuOverlay()
{
    // qDebug() << "OverlayManager::showEscapeMenuOverlay()";
    escapeMenuOverlay_->setProperty("visible", true);
}

void OverlayManager::hideEscapeMenuOverlay()
{
    // qDebug() << "OverlayManager::hideEscapeMenuOverlay()";
    escapeMenuOverlay_->setProperty("visible", false);
}

void OverlayManager::showEndGameOverlay(const QString& score)
{
    endGameOverlay_->setProperty("visible", true);
    endGameOverlay_->setProperty("message", "GAME OVER");
    endGameOverlay_->setProperty("score", score);
}

void OverlayManager::hideEndGameOverlay()
{
    endGameOverlay_->setProperty("visible", false);
    endGameOverlay_->setProperty("message", "NULL");
}
