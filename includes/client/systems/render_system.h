#pragma once

#include "client/systems/system.h"
#include <vector>

class RenderSystem : public System {
    void update(World &world, float delta) override;
};
