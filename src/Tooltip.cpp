#include "Tooltip.h"
#include <iostream>

Tooltip::Tooltip()
{
    //ctor
}

Tooltip::~Tooltip()
{
    //dtor
}

void Tooltip::draw(sf::RenderWindow* window)
{
    window->draw(sprite);
    window->draw(headerText);
    window->draw(bodyText);
}

bool Tooltip::containsPoint(sf::Vector2i& point)
{
	sf::FloatRect bounds = sprite.getGlobalBounds();
	if((point.x > bounds.left && point.x < bounds.left + bounds.width) &&
	   (point.y > bounds.top && point.y < bounds.top + bounds.height))
		return true;
	else return false;
}
