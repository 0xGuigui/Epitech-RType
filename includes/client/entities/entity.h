#pragma once

#include "client/identifiable.h"
#include <memory>
#include <vector>
#include <string>
#include <optional>
#include "client/components/component.h"

class Entity : public Identifiable {
private:
    std::vector<std::unique_ptr<Component>> _components;
public:
    const std::vector<std::unique_ptr<Component>> &components = _components;

    Entity();

    template<typename T>
    [[maybe_unused]] std::optional<T &>getComponent() const;

    template<typename T, typename... Args>
    [[maybe_unused]] void addComponent(Args&&... args);

    template<typename T>
    void removeComponent();

    ~Entity() override = default;
};
