#pragma once

#include "client/components/component.h"
#include "SFML/Graphics.hpp"

class HitboxComponent : public Component {
private:
    sf::FloatRect _hitbox;
public:
    const sf::FloatRect &hitbox = _hitbox;

    HitboxComponent() = default;

    void setHitbox(const sf::FloatRect &hb);
};
