#include "client/world.h"
#include "client/entities/entity.h"
#include "client/components/component.h"
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

template<typename Component, typename ...Args>
std::vector<std::shared_ptr<Entity>> World::getEntities() {

    if (std::is_same<Component, ::Component>())
        return _entities;

    std::vector<std::shared_ptr<Entity>> ent = _entities;

    std::erase_if(ent, [](const std::shared_ptr<Entity> &e) -> bool {
        return e->getComponent<Component>() == std::nullopt;
    });

    std::vector<std::shared_ptr<Entity>> result = getEntities<Args...>();

    std::erase_if(result.begin(), result.end(), [&ent](const std::shared_ptr<Entity> &e) -> bool {
        return std::count(ent.begin(), ent.end(), e) == 0;
    });
    return result;
}

void World::update() {
    const float delta = _timer.getElapsedTime().asSeconds();

    for (std::shared_ptr<System> &system : _systems)
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
