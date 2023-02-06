#include "client/world.h"
#include "client/components/component.h"

void World::removeEntity(const Entity &entity) {
    for (auto it = _entities.begin(); it != _entities.end(); it++) {
        // since Entity inherits from Identifiable, it has a unique id, which we can find the corresponding entity with
        if ((*it)->getId() == entity.getId()) {
            _entities.erase(it);
            break;
        }
    }
}

void World::update(sf::RenderWindow &window) {
    const float delta = _timer.restart().asSeconds();

    for (std::shared_ptr<System> &system : _systems) {
        System &type = *system;
        // Render system cannot be disabled
        if (system->isEnabled() || typeid(type) != typeid(RenderSystem))
            system->update(window, *this, delta);
    }
    // Clean up code to clean erased entities
    std::erase_if(_entities, [](const std::shared_ptr<Entity> &e) -> bool {
        return e->isErased();
    });
}

[[maybe_unused]] std::string World::generateId() {
    // id_giver is static to not generate the same id twice
    static int id_giver = 0;
    std::string id = std::to_string(id_giver);

    id_giver++;
    return id;
}
