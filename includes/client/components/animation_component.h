#pragma once

#include "client/components/components.h"
#include <vector>

class AnimationComponent : public Component {
private:
    std::shared_ptr<RenderComponent> _render_ptr;
    std::vector<sf::Rect<int>> _positions;
    int _i = 0;
    float _delta = 0;
    float _delay = 0;
public:
    AnimationComponent(std::shared_ptr<RenderComponent> &renderComponent, const std::vector<sf::Rect<int>> &positions, const float &delay = 0);

    void setAnimation(std::shared_ptr<RenderComponent> &renderComponent, const std::vector<sf::Rect<int>> &positions, const float &delay = 0);

    void animate(const float &delta = 0);

    void cast() const override {};
};
