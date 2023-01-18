#pragma once

#include <vector>
#include <array>
#include <optional>
#include "SFML/Graphics.hpp"
#include "components.h"

struct layer {
    std::vector<UiComponent *> components;
    // tell if the menu take the entire screen or not
    bool full_screen = false;
    bool render = true;
};

class UiSystem {
private:
    std::vector<layer> _layers;

    void computeRenderedLayers();

public:
    UiSystem() = default;

    void addLayer(const layer &layer);

    void addLayer(const std::vector<UiComponent *>& components, bool full_screen = false, bool render = true);

    void addLayerComponent(UiComponent &component, int layer);

    void removeLayer(std::optional<int> layer = std::nullopt);

    void removeLayerComponent(int layer, std::optional<int> component = std::nullopt);

    void removeLayerComponent(UiComponent &component);
};
