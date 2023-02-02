#include "client/components/health_component.h"

HealthComponent::HealthComponent(const float &hp) {
    _health = hp;
}

void HealthComponent::setHealth(const float &hp) {
    _health = hp;
}

void HealthComponent::setOnDeath(std::function<void()> &function) {
    _onDeath = function;
}
