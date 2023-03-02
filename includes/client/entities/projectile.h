#pragma once

#include "client/entities/entity.h"

class Projectile : public Entity {
private:
    std::shared_ptr<Entity> _theCreator;
public:
    explicit Projectile(const std::shared_ptr<Entity>& creator = nullptr);

    void setCreator(const std::shared_ptr<Entity> &creator);

    std::shared_ptr<Entity> getCreator();

    void cast() const override {};
};
