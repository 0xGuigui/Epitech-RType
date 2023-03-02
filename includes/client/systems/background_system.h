#pragma once

#include "client/systems/system.h"

class BackgroundSystem : public System {
public:
    void update(sf::RenderWindow &window, World &world, float delta) override;

    void cast() const override {};
};
