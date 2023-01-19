#pragma once

#include <vector>
#include <array>
#include <optional>
#include "SFML/Graphics.hpp"
#include "components.h"
#include "lib/error.h"

#define UI_LAYER_LIMIT 10

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
};
