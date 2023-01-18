#include "client/ui/core.h"

void UiSystem::computeRenderedLayers() {
    bool render = true;

    for (int i = static_cast<int>(_layers.size()) - 1; i >= 0; i--) {
        if (_layers[i].full_screen) {
            render = false;
        }
        _layers[i].render = render;
    }
}

void UiSystem::addLayer(const layer &layer) {
    _layers.push_back(layer);
    computeRenderedLayers();
}

void UiSystem::addLayer(const std::vector<UiComponent *> &components, bool full_screen, bool render) {
    this->addLayer({components, full_screen, render});
}

void UiSystem::addLayerComponent(UiComponent &component, int layer) {
    _layers[layer].components.push_back(&component);
}

void UiSystem::removeLayer(std::optional<int> layer) {
    if (layer.has_value()) {
        _layers.erase(_layers.begin() + layer.value());
    } else {
        _layers.pop_back();
    }
    computeRenderedLayers();
}

void UiSystem::removeLayerComponent(int layer, std::optional<int> component) {
    if (component.has_value()) {
        _layers[layer].components.erase(_layers[layer].components.begin() + component.value());
    } else {
        _layers[layer].components.pop_back();
    }
}

void UiSystem::removeLayerComponent(UiComponent &component) {
    for (auto &layer: _layers) {
        for (auto &layer_component: layer.components) {
            if (layer_component == &component) {
                layer.components.erase(std::find(layer.components.begin(), layer.components.end(), &component));
                return;
            }
        }
    }
}
