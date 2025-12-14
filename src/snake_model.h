#pragma once

#include <QAbstractListModel>
#include <QVariantMap>
#include "coordinates.h"
#include "game_config.h"
#include "snake.h"

/*
  SnakeModel stores the snake as a sequence of grid Coordinates.
  QML will ask for the model via count/get(index) or via roles positionX/positionY.
*/
class SnakeModel : public QAbstractListModel
{
    Q_OBJECT

public slots:
    void syncWithSnake();

public:
    enum Roles
    {
        positionXRole = Qt::UserRole + 1,
        positionYRole,
        snakeHeadMovementDirectionRole
    };

    explicit SnakeModel(const GameConfig& config, const Snake& snake);

    // QAbstractItemModel interface
    [[nodiscard]] int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    [[nodiscard]] QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

private:
    void updateSnakeHeadMovementDirection(const Direction& snakeHeadMovementDirection);
    void updateSegmentsCoordinates(const std::vector<Coordinates>& newSegmentsCoordinates);

    const GameConfig& config_;
    std::vector<Coordinates> segmentsCoordinates_; // stored in grid coordinates
    Direction snakeHeadMovementDirection_ {};

    const Snake& snake_;
};
