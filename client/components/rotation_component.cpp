#include "client/components/rotation_component.h"

RotationComponent::RotationComponent(const float &rotation) : Component() {
    _rotation = rotation;
}

void RotationComponent::setRotation(const float &rotation) {
    _rotation = rotation;
}
