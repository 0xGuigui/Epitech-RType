#pragma once

#include "client/identifiable.h"
#include <string>

class Component : public Identifiable {
public:
    Component();

    ~Component() override = default;
};
