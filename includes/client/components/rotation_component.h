#include "SFML/Graphics.hpp"
#include "component.h"

class RotationComponent : public Component {
private:
    float _rotation;
public:
    const float &rotation = _rotation;

    explicit RotationComponent(const float &rota = 0);

    void setRotation(const float &rota);
};
