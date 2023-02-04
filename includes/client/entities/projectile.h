#pragma once

#include "client/entities/entity.h"

class Projectile : public Entity {
private:
    std::shared_ptr<Entity> _theCreator;
public:
    Projectile(const std::shared_ptr<Entity>& creator = nullptr);

    std::shared_ptr<Entity> getCreator();

    void cast() const override {};
};
