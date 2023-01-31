#pragma once

#include "client/systems/system.h"

class MovementSystem : public System {
public:
    void update(sf::RenderWindow &window, World &world, float delta) override;
};
