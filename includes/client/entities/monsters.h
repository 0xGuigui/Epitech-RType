//
// Created by Guilhem Jéhanno on 03/02/2023.
//

#ifndef R_TYPE_MONSTERS_H
#define R_TYPE_MONSTERS_H

#include "client/entities/Entity.h"
#include "client/components/components.h"
#include "client/rtype.h"

enum monstersType {
    bouboulle = 0,
    vaisseau = 1,
    alien = 2,
    haricot = 3,
};

class Monsters : public Entity {
private:
public:
    explicit Monsters(monstersType monstersType = bouboulle);

    void cast() const override {};
};

#endif //R_TYPE_MONSTERS_H
