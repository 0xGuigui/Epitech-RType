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

    void bind(const sf::Keyboard::Key &key, const std::function<void()> &onPress = []() {}, const std::function<void()> &onRelease = []() {});

    void bind(const sf::Keyboard::Key &key, const std::pair<std::function<void()>, std::function<void()>> &pair);

    [[maybe_unused]] void setOnPress(const sf::Keyboard::Key &key, std::function<void()> &onPress);

    [[maybe_unused]] void setOnRelease(const sf::Keyboard::Key &key, std::function<void()> &onRelease);

    [[maybe_unused]] void rebind(const sf::Keyboard::Key &oldKey, const sf::Keyboard::Key &newKey, const bool &override);

    [[maybe_unused]] void unbind(const sf::Keyboard::Key &key);

    void update(const sf::Event &event);

    auto begin();

    [[nodiscard]] auto begin() const;

    auto end();

    [[nodiscard]] auto end() const;

    auto &operator[](const sf::Keyboard::Key &key);
};
