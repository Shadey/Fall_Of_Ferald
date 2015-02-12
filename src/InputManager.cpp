#include "InputManager.h"
#include <iostream>

InputManager::InputManager()
{
    keyBinds["up"] = sf::Keyboard::W;
    keyBinds["down"] = sf::Keyboard::S;
    keyBinds["left"] = sf::Keyboard::A;
    keyBinds["right"] = sf::Keyboard::D;
    keyBinds["confirm"] = sf::Keyboard::Return;
    keyBinds["cancel"] = sf::Keyboard::BackSpace;
}

InputManager::~InputManager()
{
    //dtor
}

void InputManager::update()
{
    for(int i = 0; i < sf::Keyboard::KeyCount; i++)
    {
        previousPressedKeys[i] = pressedKeys[i];
        pressedKeys[i] = sf::Keyboard::isKeyPressed( (sf::Keyboard::Key)i );
    }
}

bool InputManager::pressedOnce(std::string keyName)
{
    if(pressedKeys[keyBinds[keyName]] && !previousPressedKeys[keyBinds[keyName]])
        return true;
    else return false;
}

bool InputManager::validKeyDown()
{
    std::map<std::string, sf::Keyboard::Key>::iterator mapItr;

    for(mapItr = keyBinds.begin(); mapItr != keyBinds.end(); ++mapItr)
    {
        if(pressedOnce(mapItr->first) &&
           (mapItr->first != "confirm" || mapItr->first != "cancel"))
        {
            return true;
        }
    }
    return false;
}
