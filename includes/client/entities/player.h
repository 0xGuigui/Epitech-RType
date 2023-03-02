#pragma once

#include "client/entities/entity.h"

enum PlayerColor {
    Cyan = 0,
    Pink = 1,
    Green = 2,
    Red = 3,
    Blue = 4
};

class Player : public Entity {
private:
public:
    explicit Player(PlayerColor playerColor = Cyan);

    void setColor(PlayerColor playerColor = Cyan);

    void cast() const override {};
};
