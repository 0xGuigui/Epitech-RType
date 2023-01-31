#include "client/entities/entity.h"
#include "client/components/component.h"

Entity::Entity() : Identifiable() {}

void Entity::eraseSelf() {
    _cleanup = true;
}

bool Entity::isErased() const {
    return _cleanup;
}
