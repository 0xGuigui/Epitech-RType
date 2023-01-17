#include "keyboard_manager.h"

void KeyboardManager::bind(sf::Keyboard::Key &key, const std::function<void()> &onPress, const std::function<void()> &onRelease) {
    _map[key] = {onPress, onRelease};
}

[[maybe_unused]] void KeyboardManager::setOnPress(sf::Keyboard::Key &key, std::function<void()> &onPress) {
    std::function<void()> onRelease = []() {};

    if (_map.count(key))
        onRelease = _map[key].second;
    bind(key, onPress, onRelease);
}

[[maybe_unused]] void KeyboardManager::setOnRelease(sf::Keyboard::Key &key, std::function<void()> &onRelease) {
    std::function<void()> onPress = []() {};

    if (_map.count(key))
        onPress = _map[key].first;
    bind(key, onPress, onRelease);
}

[[maybe_unused]] void KeyboardManager::unbind(sf::Keyboard::Key &key) {
    _map.erase(key);
}

void KeyboardManager::update(sf::Event &event) {
    const sf::Keyboard::Key key = event.key.code;

    if (_map.count(key)) {
        const auto &[onPress, onRelease] = _map[key];

        if (event.type == sf::Event::KeyPressed)
            onPress();
        if (event.type == sf::Event::KeyReleased)
            onRelease();
    }
}

auto KeyboardManager::begin() {
    return _map.begin();
}

[[nodiscard]] auto KeyboardManager::begin() const {
    return _map.begin();
}

auto KeyboardManager::end() {
    return _map.end();
}

[[nodiscard]] auto KeyboardManager::end() const {
    return _map.end();
}

auto &KeyboardManager::operator[](const sf::Keyboard::Key &key) {
    return _map[key];
}
