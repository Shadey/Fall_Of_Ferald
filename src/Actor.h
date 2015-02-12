// The actor class acts as a base for any
#ifndef ACTOR_H
#define ACTOR_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Asset.h"

class Actor
{

	public:
		Actor(int _x, int _y, int _layer);

		// Accessor functions
		sf::Vector2f getPosition();
		int getLayer();
		sf::Rect<int> getBounds();
		void setBounds(sf::Rect<int> bounds);
		sf::Sprite getSprite();
	protected:
		sf::Sprite sprite;              // contains the media and it's location onscreen
		sf::Rect<int> bounds;		    // The bounding box of the actor
		int layer;                      // The order in which to draw the sprite
};
#endif
