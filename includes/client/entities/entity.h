#pragma once

#include "client/identifiable.h"
#include <memory>
#include <vector>
#include <string>
#include <optional>
#include "client/components/component.h"

class Entity : public Identifiable {
private:
    std::vector<std::shared_ptr<Component>> _components;
public:
    const std::vector<std::shared_ptr<Component>> &components = _components;

    Entity();

    template<typename T>
    std::optional<std::shared_ptr<T>>getComponent() const;

    template<typename T, typename... Args>
    [[maybe_unused]] void addComponent(Args&&... args);

    template<typename T>
    void removeComponent();

    ~Entity() override = default;
};
