#include "client/identifiable.h"
#include "client/world.h"

Identifiable::Identifiable() {
    _id = World::generateId();
}

[[nodiscard]] const std::string &Identifiable::getId() const {
    return _id;
}

bool Identifiable::operator == (const Identifiable &identifiable) const {
    return _id == identifiable._id;
}

bool Identifiable::operator != (const Identifiable &identifiable) const {
    return _id != identifiable._id;
}
