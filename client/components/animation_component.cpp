#include "client/components/animation_component.h"


AnimationComponent::AnimationComponent(std::shared_ptr<RenderComponent> &renderComponent,
                                       const std::vector<sf::Rect<int>> &positions, const float &delay) {
    _render_ptr = renderComponent;
    _positions = positions;
    _delay = delay;
}

void AnimationComponent::setAnimation(std::shared_ptr<RenderComponent> &renderComponent,
                                      const std::vector<sf::Rect<int>> &positions, const float &delay) {
    _render_ptr = renderComponent;
    _positions = positions;
    _delay = delay;
}

void AnimationComponent::animate(const float &delta) {
    _delta += delta;

    if (_delta < _delay)
        return;
    if (_i == _positions.size())
        _i = 0;
    _render_ptr->getRender().setTextureRect(_positions[_i]);
    _i++;
    _delta -= _delay;
}
