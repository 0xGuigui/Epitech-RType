#pragma once

#include "client/components/component.h"
#include <functional>

class HealthComponent : public Component {
private:
    float _health = 0;
    float _damage = 0;
    std::function<void()> _onDeath = []() {};
public:
    explicit HealthComponent(const float &hp = 0, const float &dmg = 0);

    void setHealth(const float &hp);

    void setDamage(const float &dmg);

    void setOnDeath(const std::function<void()> &function);

    void onDeath();

    float &getHealth();

    float &getDamage();

    void cast() const override {};
};
