#pragma once

#include "component.h"
#include "SFML/Graphics.hpp"

class VelocityComponent : public Component {
private:
    sf::Vector2<float> _velocity;
public:
    const sf::Vector2<float> &velocity = _velocity;

    explicit VelocityComponent(const float &x = 0, const float &y = 0);

    explicit VelocityComponent(const sf::Vector2<float> &vector2);

    void setVelocity(const float &x = 0, const float &y = 0);

    void setVelocity(sf::Vector2<float> &v);

    void cast() const override {};
};
