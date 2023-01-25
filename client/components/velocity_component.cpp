#include "client/components/velocity_component.h"

VelocityComponent::VelocityComponent(const float &x, const float &y) : Component() {
    _velocity = {x, y};
}

void VelocityComponent::setVelocity(const float &x, const float &y) {
    _velocity = {x, y};
}

void VelocityComponent::setVelocity(sf::Vector2<float> &v) {
    _velocity = v;
}
