#pragma once
#include "SFML/Graphics.hpp"

class World;

class System {
private:
    bool _enabled = true;
public:
    virtual ~System() = default;

    void setEnabled(bool enabled);

    [[nodiscard]] bool isEnabled() const;

    /*
     * Updates the system by providing the render window, the world class,
     * and the delta time which corresponds to how many seconds has passed
     * since the last call of this function
     */
    virtual void update(sf::RenderWindow &window, World &world, float delta) = 0;
    virtual void cast() const {};
};
