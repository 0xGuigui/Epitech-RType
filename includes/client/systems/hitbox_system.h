#pragma once

#include "client/systems/system.h"

class HitboxSystem : public System {
public:
    void update(sf::RenderWindow &window, World &world, float delta) override;
};
