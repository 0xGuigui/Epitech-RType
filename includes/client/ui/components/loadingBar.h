#ifndef R_TYPE_LOADINGBAR_H
#define R_TYPE_LOADINGBAR_H

#include "client/ui/core.h"

class LoadingBar
{
public:
    LoadingBar(const sf::Vector2f &size, const sf::Color &color);
    void setPosition(const sf::Vector2f &pos);
    void setPercentage(float percentage);
    void setColor(const sf::Color &color);
    void draw(sf::RenderTarget &target) const;

private:
    sf::RectangleShape background;
    sf::RectangleShape fill;
    sf::Color colors;
};

#endif //R_TYPE_LOADINGBAR_H
