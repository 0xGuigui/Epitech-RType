#include "client/entities/entity.h"
#include "client/components/component.h"

Entity::Entity() : Identifiable() {}

template<typename T>
[[maybe_unused]] std::optional<T &>Entity::getComponent() {
    const auto &it = std::find_if(_components.begin(), _components.end(), [](const std::unique_ptr<Component> &c) {
        return dynamic_cast<T>(*c) != nullptr;
    });

    return std::make_optional(it != nullptr ? *it : std::nullopt);
}

template<typename T, typename ...Args>
[[maybe_unused]] void Entity::addComponent(Args &&...args) {
    const auto &it = std::find_if(_components.begin(), _components.end(), [](const std::unique_ptr<Component> &c) {
        return dynamic_cast<T>(*c) != nullptr;
    });

    if (it != _components.end())
        removeComponent<T>();
    _components.emplace_back(std::make_unique<Component>(std::forward<Args>(args)...));
}

template<typename T>
void Entity::removeComponent() {
    for (auto it = _components.begin(); it != _components.end(); it++) {
        if (dynamic_cast<T>(*it) != nullptr) {
            _components.erase(it);
            break;
        }
    }
}
