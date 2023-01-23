#include "client/identifiable.h"
#include "client/world.h"

Identifiable::Identifiable() {
    _id = World::generateId();
}

[[maybe_unused]] const std::string &Identifiable::getId() {
    return _id;
}

bool Identifiable::operator == (const Identifiable &identifiable) {
    return _id == identifiable._id;
}

bool Identifiable::operator != (const Identifiable &identifiable) {
    return _id != identifiable._id;
}
