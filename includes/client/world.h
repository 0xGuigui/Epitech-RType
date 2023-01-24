#pragma once

#include <vector>
#include <memory>
#include <string>
#include "SFML/System.hpp"
#include "client/entities/entity.h"
#include "client/systems/system.h"

class World {
private:
    std::vector<std::unique_ptr<Entity>> _entities;
    std::vector<std::unique_ptr<System>> _systems;
    sf::Clock _timer;
public:
    const std::vector<std::unique_ptr<Entity>> &entities = _entities;
    const std::vector<std::unique_ptr<System>> &systems = _systems;

    World() = default;
    ~World() = default;

    [[maybe_unused]] Entity &createEntity();

    void removeEntity(const Entity &entity);

    void update();

    static std::string generateId();
};
