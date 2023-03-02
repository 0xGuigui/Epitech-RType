#pragma once

#include "client/identifiable.h"
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <optional>
#include <type_traits>
#include "client/components/component.h"

class Entity : public Identifiable {
private:
    std::vector<std::shared_ptr<Component>> _components;
    bool _cleanup = false;
public:
    Entity();

    // Gets the corresponding component of the Entity based on the type given as template parameter
    template<typename T, typename std::enable_if<std::is_base_of<Component, T>::value, int>::type = 0>
    std::shared_ptr<T> getComponent() const {
        const auto &it = std::find_if(_components.begin(), _components.end(), [](const std::shared_ptr<Component> &c) -> bool {
            // Checks if the Component is castable into the type given in parameter
            return dynamic_cast<T *>(c.get());
        });

        // If it didn't find a corresponding component, the function returns an empty shared_ptr
        return it != _components.end() ? std::static_pointer_cast<T>(*it) : std::shared_ptr<T>();
    };

    // If the given type doesn't inherits from the Component class, it returns an empty shared_ptr
    template<typename T, typename std::enable_if<!std::is_base_of<Component, T>::value, int>::type = 0>
    std::shared_ptr<T> getComponent() const {
        return std::shared_ptr<T>();
    };

    [[nodiscard]] std::vector<std::shared_ptr<Component>> getComponents() const {
        return _components;
    };

    // To call this function, give the type of the Component in the template argument and the arguments needed to construct this class in the function arguments
    template<typename T, typename... Args>
    [[maybe_unused]] void addComponent(Args&&... args) {
        const auto &it = std::find_if(_components.begin(), _components.end(), [](const std::shared_ptr<Component> &c) {
            // Checks if the Component is castable into the type given in parameter
            return dynamic_cast<T *>(c.get());
        });

        // If a component was found, remove it
        if (it != _components.end())
            removeComponent<T>();
        /* Constructs a shared_ptr of the desired type in the back of the vector,
         * and pass on the args given in the function to the desired class's constructor
         */
        _components.emplace_back(std::make_shared<T>(std::forward<Args>(args)...));
    };

    template<typename T>
    void removeComponent() {
        for (auto it = _components.begin(); it != _components.end(); it++) {
            // Checks if the Component is castable into the type given in parameter
            if (dynamic_cast<T *>(it->get())) {
                _components.erase(it);
                break;
            }
        }
    };

    // Put the entity in a cleanup state, doesn't erase it right away
    void eraseSelf();

    [[nodiscard]] bool isErased() const;

    ~Entity() override = default;

    // Must include in classes that inherits from Entity ! It makes the class polymorphic (or else you can't cast it to Entity)
    virtual void cast() const {};
};
