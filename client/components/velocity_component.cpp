#include "client/components/velocity_component.h"

VelocityComponent::VelocityComponent(const float &x, const float &y) {
    _velocity = {x, y};
}

VelocityComponent::VelocityComponent(const sf::Vector2<float> &vector2) {
    _velocity = vector2;
}

void VelocityComponent::setVelocity(const float &x, const float &y) {
    _velocity = {x, y};
}

void VelocityComponent::setVelocity(const sf::Vector2<float> &v) {
    _velocity = v;
}

sf::Vector2<float> VelocityComponent::getVelocity() {
    return _velocity;
}
