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
