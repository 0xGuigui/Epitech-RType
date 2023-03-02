#pragma once

#include "client/entities/entity.h"

class IndestructibleObstacle : public Entity {
private:
public:
    explicit IndestructibleObstacle();

    void cast() const override {};
};