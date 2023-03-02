//
// Created by Guilhem Jéhanno on 04/02/2023.
//

#ifndef R_TYPE_POWERUP_H
#define R_TYPE_POWERUP_H

#include "client/entities/entity.h"
#include "client/components/components.h"
#include "client/rtype.h"

enum powerupType {
    speed = 0,
    health = 1,
    damage = 2,
    shield = 3,
};

class PowerUp : public Entity {
private:
public:
    explicit PowerUp(powerupType powerUpType = speed);

    void cast() const override {};
};

#endif //R_TYPE_POWERUP_H
