#ifndef TOOLTIP_H
#define TOOLTIP_H
#include <string>
#include <SFML/Graphics.hpp>


class Tooltip
{
    friend class UserInterface; // Allowing the UI class to access tooltip members

    public:
        Tooltip();
        virtual ~Tooltip();
        sf::Sprite getSprite() {return sprite;}
        void draw(sf::RenderWindow *window);
    private:
        sf::Sprite sprite;
        sf::Text headerText;
        sf::Text bodyText;
        bool isMoveable;        // Wether or not the _user_ can move or close the tooltip
        bool isCloseable;
};

#endif // TOOLTIP_H
