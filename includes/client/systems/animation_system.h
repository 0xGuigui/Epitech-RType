#pragma once

#include "client/systems/system.h"

class AnimationSystem : public System {
    void update(sf::RenderWindow &window, World &world, float delta) override;

    void cast() const override {};
};
