#pragma once

#include <vector>
#include <functional>
#include "SFML/Window.hpp"
#include <unordered_map>
#include <tuple>

class KeyboardManager {
private:
    std::unordered_map<sf::Keyboard::Key, std::pair<std::function<void()>, std::function<void()>>> _map;
public:
    KeyboardManager() = default;

    /* Binds two functions, respectively onPress and onRelease to a key of the keyboard
     * If that key is pressed, the onPress function will called,
     * If that key is released, the onRelease function will be called
     * If the override parameter is false and the key is already bound, the function will throw an error
     */
    void bind(const sf::Keyboard::Key &key, const std::function<void()> &onPress = []() {}, const std::function<void()> &onRelease = []() {}, const bool &override = false);

    void bind(const sf::Keyboard::Key &key, const std::pair<std::function<void()>, std::function<void()>> &pair, const bool &override = false);

    [[maybe_unused]] void setOnPress(const sf::Keyboard::Key &key, std::function<void()> &onPress, const bool &override = false);

    [[maybe_unused]] void setOnRelease(const sf::Keyboard::Key &key, std::function<void()> &onRelease, const bool &override = false);

    [[maybe_unused]] void rebind(const sf::Keyboard::Key &oldKey, const sf::Keyboard::Key &newKey, const bool &override = false);

    [[maybe_unused]] void unbind(const sf::Keyboard::Key &key);

    void update(const sf::Event &event);

    auto begin();

    [[nodiscard]] auto begin() const;

    auto end();

    [[nodiscard]] auto end() const;

    auto &operator[](const sf::Keyboard::Key &key);
};
