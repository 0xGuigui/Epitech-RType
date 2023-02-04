#pragma once
#include "SFML/Graphics.hpp"

class World;

class System {
private:
    bool _enabled = true;
    bool _updatable = true;
public:
    virtual ~System() = default;

    void setEnabled(bool enabled);

    void setUpdatable(bool updatable);

    [[nodiscard]] bool isEnabled() const;

    [[nodiscard]] bool isUpdatable() const;

    virtual void update(sf::RenderWindow &window, World &world, float delta) = 0;
    virtual void cast() const {};
};
