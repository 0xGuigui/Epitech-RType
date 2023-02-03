#pragma once

#include "client/entities/entity.h"

class Projectile : public Entity {
public:
    Projectile();

    void cast() const override {};
};
