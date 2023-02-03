#pragma once

#include "client/identifiable.h"
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <optional>
#include "client/components/component.h"

class Entity : public Identifiable {
private:
    std::vector<std::shared_ptr<Component>> _components;
    bool _cleanup = false;
public:
    const std::vector<std::shared_ptr<Component>> &components = _components;

    Entity();

    template<typename T>
    std::shared_ptr<T> getComponent() const {
        const auto &it = std::find_if(_components.begin(), _components.end(), [](const std::shared_ptr<Component> &c) -> bool {
            return dynamic_cast<T *>(c.get());
        });

        return it != _components.end() ? std::static_pointer_cast<T>(*it) : std::shared_ptr<T>();
    };

    template<typename T, typename... Args>
    [[maybe_unused]] void addComponent(Args&&... args) {
        const auto &it = std::find_if(_components.begin(), _components.end(), [](const std::shared_ptr<Component> &c) {
            return dynamic_cast<T *>(c.get());
        });

        if (it != _components.end())
            removeComponent<T>();
        _components.emplace_back(std::make_shared<T>(std::forward<Args>(args)...));
    };

    template<typename T>
    void removeComponent() {
        for (auto it = _components.begin(); it != _components.end(); it++) {
            if (dynamic_cast<T *>(it->get())) {
                _components.erase(it);
                break;
            }
        }
    };

    void eraseSelf();

    [[nodiscard]] bool isErased() const;

    ~Entity() override = default;

    virtual void cast() const {};
};
