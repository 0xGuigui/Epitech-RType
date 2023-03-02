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

void HealthComponent::setOnDeath(const std::function<void()> &function) {
    _onDeath = function;
}

void HealthComponent::onDeath() {
    _onDeath();
}

float &HealthComponent::getHealth() {
    return _health;
}

float &HealthComponent::getDamage() {
    return _damage;
}
