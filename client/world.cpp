#include "client/world.h"
#include "client/entities/entity.h"
#include "client/components/component.h"
#include "SFML/System.hpp"
#include "client/systems/system.h"

[[maybe_unused]] Entity &World::createEntity() {
    _entities.emplace_back();

    return *_entities.back();
}

void World::removeEntity(const Entity &entity) {
    for (auto it = _entities.begin(); it != _entities.end(); it++) {
        if ((*it)->getId() == entity.getId()) {
            _entities.erase(it);
            break;
        }
    }
}

void World::update() {
    const float delta = _timer.getElapsedTime().asSeconds();

    for (std::unique_ptr<System> &system : _systems)
        system->update(*this, delta);
    _timer.restart();
}

[[maybe_unused]] std::string World::generateId() {
    static std::string id_giver = "0";
    std::string id = id_giver;

    if (id_giver.back() == '9') {
        id_giver.back() = '0';
        id_giver.push_back('0');
    } else
        id_giver.back()++;
    return id;
}
