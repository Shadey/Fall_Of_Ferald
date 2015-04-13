#ifndef TILEHIGHLIGHT_H
#define TILEHIGHLIGHT_H
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class TileHighlight
{
	public:
		TileHighlight(int x, int y, sf::Color colour, int tileSize);
		void draw(sf::RenderWindow* window);
		inline const sf::Color& getColour() { return highlight.getFillColor(); }
	private:
		sf::RectangleShape highlight;
};
#endif //TILEHIGHLIGHT_H
