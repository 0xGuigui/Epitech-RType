#include "client/world.h"
#include "client/entities/entity.h"
#include "client/components/component.h"

[[maybe_unused]] Entity &World::createEntity() {
    _entities.emplace_back();

    return *_entities.back();
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
