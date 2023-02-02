#pragma once

#include "client/components/component.h"

class HealthComponent : public Component {
private:
    float _health = 0;
    std::function<void()> _onDeath;
public:
    const float &health = _health;
    const std::function<void()> &onDeath = _onDeath;

    explicit HealthComponent(const float &hp);

    void setHealth(const float &hp);

    void setOnDeath(std::function<void()> &function);
};
