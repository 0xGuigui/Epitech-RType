#include "client/entities/entity.h"
#include "client/components/scale_component.h"

Entity::Entity() : Identifiable() {
    addComponent<ScaleComponent>();
}

void Entity::eraseSelf() {
    _cleanup = true;
}

bool Entity::isErased() const {
    return _cleanup;
}
