#pragma once

#include "client/systems/system.h"

class MovementSystem : public System {
public:
    void update(World &world, float delta) override;
};
