#include "client/components/health_component.h"

HealthComponent::HealthComponent(const float &hp, const float &dmg) {
    _health = hp;
    _damage = dmg;
}

void HealthComponent::setDamage(const float &dmg) {
    _damage = dmg;
}

void HealthComponent::setHealth(const float &hp) {
    _health = hp;
}

void HealthComponent::setOnDeath(std::function<void()> &function) {
    _onDeath = function;
}
