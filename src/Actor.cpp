 #include "Actor.h"

// Constructor
 Actor::Actor(int _x, int _y, int _layer)
 {
	sprite.setPosition(_x, _y);
 }

 // Accessor methods
 sf::Vector2f Actor::getPosition() {return sprite.getPosition();}
 int Actor::getLayer() { return layer; }
 sf::Rect<int> Actor::getBounds() { return bounds; }
 void Actor::setBounds(sf::Rect<int> _bounds) { bounds = _bounds; }
 sf::Sprite Actor::getSprite() {return sprite;}
