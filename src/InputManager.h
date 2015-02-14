#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include <map>

class InputManager
{
    public:
        InputManager();
        virtual ~InputManager();
        void update(sf::RenderWindow& window);
        bool pressedOnce(std::string keyName);
		bool pressedOnce(sf::Mouse::Button button);
        bool validKeyDown();
		inline sf::Vector2i getMousePosition() { return mousePosition; }
		inline sf::Vector2i getPrevMousePosition() { return previousMousePosition; }
    private:
        bool pressedKeys[sf::Keyboard::KeyCount];
		bool pressedMouseButtons[sf::Mouse::ButtonCount];
		bool previousPressedMouseButtons[sf::Mouse::ButtonCount];
        bool previousPressedKeys[sf::Keyboard::KeyCount];
        std::map<std::string, sf::Keyboard::Key> keyBinds;
		sf::Vector2i mousePosition;
		sf::Vector2i previousMousePosition;
};

#endif // INPUTMANAGER_H

