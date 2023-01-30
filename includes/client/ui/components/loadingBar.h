#ifndef R_TYPE_LOADINGBAR_H
#define R_TYPE_LOADINGBAR_H

#include "client/ui/core.h"

class LoadingBar
{
public:
    LoadingBar(const sf::Vector2f &size, const sf::Color &color)
            : m_background(size), m_fill(sf::Vector2f(0.f, size.y)), m_color(color)
    {
        m_background.setFillColor(sf::Color(100, 100, 100));
        m_fill.setFillColor(color);
    }

    void setPosition(const sf::Vector2f &pos)
    {
        m_background.setPosition(pos);
        m_fill.setPosition(pos);
    }

    void setPercentage(float percentage)
    {
        m_fill.setSize(sf::Vector2f(m_background.getSize().x * percentage, m_background.getSize().y));
    }

    void setColor(const sf::Color &color)
    {
        m_color = color;
        m_fill.setFillColor(color);
    }

    void draw(sf::RenderTarget &target) const
    {
        target.draw(m_background);
        target.draw(m_fill);
    }

private:
    sf::RectangleShape m_background;
    sf::RectangleShape m_fill;
    sf::Color m_color;
};

#endif //R_TYPE_LOADINGBAR_H
