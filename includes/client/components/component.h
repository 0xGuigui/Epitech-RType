#pragma once

#include <string>

class Component {
public:
    ~Component() = default;

    virtual void cast() const {};
};
