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

void UiSystem::checkLayer(int layer) const {
    if (layer < 0 || layer >= _layers.size()) {
        throw UiError("Layer " + std::to_string(layer) + " does not exist");
    }
}

void UiSystem::checkComponent(int layer, int component) const {
    checkLayer(layer);
    if (component < 0 || component >= _layers[layer].components.size()) {
        throw UiError("Component " + std::to_string(component) + " does not exist");
    }
}

void UiSystem::addLayer(const layer &layer) {
    if (_layers.size() >= UI_LAYER_LIMIT) {
        throw UiError("Layer limit reached");
    }
    _layers.push_back(layer);
    computeRenderedLayers();
}

void UiSystem::addLayer(const std::vector<IUiComponent *> &components, bool full_screen) {
    this->addLayer({components, full_screen, true});
}

void UiSystem::addLayerComponent(IUiComponent &component, int layer) {
    checkLayer(layer);
    _layers[layer].components.push_back(&component);
}

void UiSystem::removeLayer(std::optional<int> layer) {
    checkLayer(layer.value_or(_layers.size() - 1));
    if (layer.has_value()) {
        _layers.erase(_layers.begin() + layer.value());
    } else {
        _layers.pop_back();
    }
    computeRenderedLayers();
}

void UiSystem::removeLayerComponent(int layer, std::optional<int> component) {
    checkComponent(layer, component.value_or(_layers[layer].components.size() - 1));
    if (component.has_value()) {
        _layers[layer].components.erase(_layers[layer].components.begin() + component.value());
    } else {
        _layers[layer].components.pop_back();
    }
}

void UiSystem::removeLayerComponent(IUiComponent &component) {
    for (auto &layer: _layers) {
        for (auto &layer_component: layer.components) {
            if (layer_component == &component) {
                layer.components.erase(std::find(
                        layer.components.begin(),
                        layer.components.end(),
                        &component
                ));
                return;
            }
        }
    }
    throw UiError("Component not found");
}

void UiSystem::draw(sf::RenderTarget &target, sf::RenderStates states) {
    for (auto &layer: _layers) {
        if (layer.render) {
            for (auto &component: layer.components) {
                component->draw(target, states);
            }
        }
    }
}
