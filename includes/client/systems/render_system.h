#pragma once

#include "client/systems/system.h"
#include <vector>

class RenderSystem : public System {
    void update(sf::RenderWindow &window, World &world, float delta) override;
};
