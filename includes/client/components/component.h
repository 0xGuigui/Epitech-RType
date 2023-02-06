#pragma once

#include <string>

class Component {
public:
    ~Component() = default;

    // Must include in classes that inherits from Component ! It makes the class polymorphic (or else you can't cast it to Component)
    virtual void cast() const {};
};
