#include "snake_model.h"

SnakeModel::SnakeModel(const GameConfig& config, const Snake& snake) : config_(config), snake_(snake)
{
    connect(&snake_, &Snake::stateChanged, this, &SnakeModel::syncWithSnake);
    syncWithSnake();
}

void SnakeModel::syncWithSnake()
{
    // qDebug() << "syncWithSnake";

    updateSnakeHeadMovementDirection(snake_.getMovementDirection());
    updateSegmentsCoordinates(snake_.getAllSegmentsCoordinates());
}

int SnakeModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
    {
        return 0;
    }

    return static_cast<int>(segmentsCoordinates_.size());
}

QVariant SnakeModel::data(const QModelIndex& index, const int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= static_cast<int>(segmentsCoordinates_.size()))
    {
        qWarning() << "Invalid index" << index.row() << "for SnakeModel";
        return {};
    }

    const Coordinates& coordinates = segmentsCoordinates_.at(index.row());

    switch (role)
    {
        case positionXRole: return coordinates.x_;
        case positionYRole: return coordinates.y_;
        case snakeHeadMovementDirectionRole: return static_cast<int>(snakeHeadMovementDirection_);
        default: return {};
    }
}

QHash<int, QByteArray> SnakeModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[positionXRole] = "positionXRole";
    roles[positionYRole] = "positionYRole";
    roles[snakeHeadMovementDirectionRole] = "snakeHeadMovementDirectionRole";

    return roles;
}

void SnakeModel::updateSnakeHeadMovementDirection(const Direction& snakeHeadMovementDirection)
{
    // qDebug() << "New snake head movement direction:" << static_cast<int>(snakeHeadMovementDirection);
    snakeHeadMovementDirection_ = snakeHeadMovementDirection;
}

void SnakeModel::updateSegmentsCoordinates(const std::vector<Coordinates>& newSegmentsCoordinates)
{
    const size_t oldCount = static_cast<int>(segmentsCoordinates_.size());
    const size_t newCount = static_cast<int>(newSegmentsCoordinates.size());

    // Scenario 1: same segment count, update in-place and emit dataChanged
    if (newCount == oldCount)
    {
        if (newCount == 0)
        {
            // nothing to do
            return;
        }

        // copy values
        segmentsCoordinates_ = newSegmentsCoordinates;

        const QModelIndex top = index(0, 0);
        const QModelIndex bottom = index(newCount - 1, 0);
        emit dataChanged(top, bottom, {positionXRole, positionYRole, snakeHeadMovementDirectionRole});

        return;
    }

    // Scenario 2: growth (insert rows)
    if (newCount > oldCount)
    {
        // update coordinates for existing indices (0 to oldCount-1)
        if (oldCount > 0)
        {
            for (int i = 0; i < oldCount; ++i)
            {
                segmentsCoordinates_[i] = newSegmentsCoordinates[i];
            }

            const QModelIndex top = index(0, 0);
            const QModelIndex bottom = index(oldCount - 1, 0);
            emit dataChanged(top, bottom, {positionXRole, positionYRole, snakeHeadMovementDirectionRole});
        }

        // append new rows for new segments (oldCount to newCount-1)
        beginInsertRows(QModelIndex(), oldCount, newCount - 1);
        segmentsCoordinates_.insert(segmentsCoordinates_.end(), newSegmentsCoordinates.begin() + oldCount, newSegmentsCoordinates.end());
        endInsertRows();

        return;
    }

    // Scenario 3: shrinking (remove rows) - this covers the scenario when the snake is reset
    if (newCount < oldCount) // TODO OPTIONAL refactor so that the whole model is recreated instead of shrinking
    {
        // update remaining entries first (0 .. newCount-1)
        if (newCount > 0)
        {
            for (int i = 0; i < newCount; ++i)
            {
                segmentsCoordinates_[i] = newSegmentsCoordinates[i];
            }

            const QModelIndex top = index(0, 0);
            const QModelIndex bottom = index(newCount - 1, 0);
            emit dataChanged(top, bottom, {positionXRole, positionYRole, snakeHeadMovementDirectionRole});
        }

        // remove trailing rows [newCount .. oldCount-1]
        beginRemoveRows(QModelIndex(), newCount, oldCount - 1);
        segmentsCoordinates_.erase(segmentsCoordinates_.begin() + newCount, segmentsCoordinates_.end());
        endRemoveRows();
    }
}
