#pragma once

#include <vector>
#include <optional>
#include <functional>
#include <SFML/Graphics.hpp>
#include "lib/error.h"

#define UI_LAYER_LIMIT 10

class IUiComponent {
public:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;

    virtual bool handleEvent(sf::Event &event) = 0;

    virtual ~IUiComponent() = default;
};

template<typename T>
class UiComponent : public IUiComponent, public sf::Drawable, public sf::Transformable {
protected:
    T &SFMLElement;

public:
    explicit UiComponent(T &SFMLElement) : SFMLElement(SFMLElement) {}

    T &getSFMLElement() const;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    bool handleEvent(sf::Event &event) override = 0;
};

template<typename T>
class StatelessUiComponent : public UiComponent<T> {
public:
    explicit StatelessUiComponent(T &SFMLElement) : UiComponent<T>(SFMLElement) {}

    bool handleEvent(sf::Event &event) override;
};

template<typename T>
class StatefulUiComponent : public UiComponent<T> {
public:
    explicit StatefulUiComponent(T &SFMLElement, std::function<void()> onClick) : UiComponent<T>(SFMLElement),
                                                                                  onClick(std::move(onClick)) {}

    bool handleEvent(sf::Event &event) override;

private:
    std::function<void()> onClick;
};

struct layer {
    std::vector<IUiComponent *> components;
    // tell if the menu take the entire screen or not
    bool full_screen = false;
    bool render = true;
};

class UiSystem {
private:
    std::vector<layer> _layers;

    void computeRenderedLayers();

    void checkLayer(int layer) const;

    void checkComponent(int layer, int component) const;

public:
    UiSystem() = default;

    void addLayer(const layer &layer);

    void addLayer(const std::vector<IUiComponent *> &components, bool full_screen = false);

    void addLayerComponent(IUiComponent &component, int layer);

    void removeLayer(std::optional<int> layer = std::nullopt);

    void removeLayerComponent(int layer, std::optional<int> component = std::nullopt);

    void removeLayerComponent(IUiComponent &component);

    void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default);

    void dispatchEvent(sf::Event &event);
};
