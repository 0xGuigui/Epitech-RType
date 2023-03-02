#pragma once

#include "client/entities/entity.h"

class Obstacle : public Entity {
private:
public:
    explicit Obstacle();

    void cast() const override {};
};