#pragma once

#include "client/components/component.h"
#include "SFML/Graphics.hpp"

class HitboxComponent : public Component {
private:
    sf::FloatRect _hitbox;
    std::function<void()> _onCollide;
public:
    const sf::FloatRect &hitbox = _hitbox;
    const std::function<void()> &onCollide = _onCollide;

    HitboxComponent() = default;

    HitboxComponent(const sf::FloatRect &hb, std::function<void()> function);

    HitboxComponent(const sf::Sprite &sprite, std::function<void()> function);

    void setHitbox(const sf::FloatRect &hb);

    void setHitbox(const sf::Sprite &sprite);

    void setOnCollide(std::function<void()> &collideFunction);
};
