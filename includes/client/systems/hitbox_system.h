#pragma once

#include "client/systems/system.h"

class HitboxSystem : public System {
public:
    void update(World &world, float delta) override;
};
