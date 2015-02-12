#include "TileHighlight.h"

TileHighlight::TileHighlight(int x, int y, sf::Color colour, int tileSize)
{
	highlight.setSize(sf::Vector2f(tileSize, tileSize));
	highlight.setPosition(x * tileSize, y * tileSize);
	highlight.setFillColor(colour);
}

void TileHighlight::draw(sf::RenderWindow* window)
{
	window->draw(highlight);
}
