#include "DialogueBox.h"
#include <SFML/Graphics.hpp>

DialogueBox::DialogueBox()
{
}

DialogueBox::~DialogueBox()
{
    if (openFile.is_open())
        openFile.close();
}

bool DialogueBox::openScript(const std::string& filePath)
{
    openFile.open(filePath.c_str());

    if (!openFile) return false;
    else return true;
}

void DialogueBox::nextLine()
{
    std::string line;
    std::getline(openFile, line, '|');
    name.setString(line);

    std::getline(openFile, line);
    dialogue.setString(line);

    // Updating the position of each string
    name.setPosition(sprite.getPosition().x + 180 - (name.getGlobalBounds().width / 2),
                     sprite.getPosition().y + 30  - (name.getCharacterSize() / 2));

    dialogue.setPosition(20, sprite.getPosition().y + 80);


    std::cout << std::endl;
    std::cout << "Top: " << name.getGlobalBounds().top << std::endl;
    std::cout << "Height: " << name.getGlobalBounds().height << std::endl;
}

void DialogueBox::draw(sf::RenderWindow *window)
{
    window->draw(sprite);
    window->draw(name);
    window->draw(dialogue);
}
