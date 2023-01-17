#pragma once

#include <vector>
#include <functional>
#include <SFML/Window.hpp>
#include <unordered_map>
#include <tuple>

class KeyboardManager {
private:
    std::unordered_map<sf::Keyboard::Key, std::pair<std::function<void()>, std::function<void()>>> _map;
public:
    KeyboardManager() = default;

    void bind(sf::Keyboard::Key &key, const std::function<void()> &onPress = []() {}, const std::function<void()> &onRelease = []() {});

    [[maybe_unused]] void setOnPress(sf::Keyboard::Key &key, std::function<void()> &onPress);

    [[maybe_unused]] void setOnRelease(sf::Keyboard::Key &key, std::function<void()> &onRelease);

    [[maybe_unused]] void unbind(sf::Keyboard::Key &key);

    void update(sf::Event &event);

    auto begin();

    [[nodiscard]] auto begin() const;

    auto end();

    [[nodiscard]] auto end() const;

    auto &operator[](const sf::Keyboard::Key &key);
};
