#include "loadingBar.h"

LoadingBar::LoadingBar(const sf::Vector2f &size, const sf::Color &color)
        : background(size), fill(sf::Vector2f(0.f, size.y)), colors(color)
{
    background.setFillColor(sf::Color(100, 100, 100));
    fill.setFillColor(color);
}

void LoadingBar::setPosition(const sf::Vector2f &pos)
{
    background.setPosition(pos);
    fill.setPosition(pos);
}

void LoadingBar::setPercentage(float percentage)
{
    fill.setSize(sf::Vector2f(background.getSize().x * percentage, background.getSize().y));
}

void LoadingBar::setColor(const sf::Color &color)
{
    colors = color;
    fill.setFillColor(color);
}

void LoadingBar::draw(sf::RenderTarget &target) const
{
    target.draw(background);
    target.draw(fill);
}
