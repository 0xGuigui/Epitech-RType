#pragma once

#include "client/entities/entity.h"
#include "client/components/components.h"
#include "client/rtype.h"

enum monsterType {
    bouboulle = 0,
    vaisseau = 1,
    alien = 2,
    haricot = 3,
};

class Monster : public Entity {
private:
public:
    explicit Monster(monsterType monstersType = bouboulle);

    void cast() const override {};
};
