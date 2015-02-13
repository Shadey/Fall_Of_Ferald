#include "UserInterface.h"
#include <iostream>

UserInterface::UserInterface()
{
    // Loading in the fonts required for the UI
    regularFont.loadFromFile("assets/fonts/steelfish rg.ttf");
    italicFont.loadFromFile ("assets/fonts/steelfish rg it.ttf");
}

UserInterface::~UserInterface()
{
    //dtor
}

void UserInterface::update(sf::Event::MouseMoveEvent moveEvent, sf::Event::MouseButtonEvent buttonEvent)
{
    std::list<Tooltip>::iterator itr;
    int offsetX, offsetY;       // The x and y offset to move the tooltip by

	if(buttonEvent.button == sf::Mouse::Button::Left)
		std::cout << "LMB Pressed!" << std::endl;

    for (itr = tooltips.begin(); itr != tooltips.end(); itr++)
    {
        // Checking if the cursor's location is within the tooltip
        if ( ( moveEvent.x > itr->sprite.getPosition().x && moveEvent.x < itr->sprite.getPosition().x + itr->sprite.getGlobalBounds().width)
            && ( moveEvent.y > itr->sprite.getPosition().y && moveEvent.y < itr->sprite.getPosition().y + itr-> sprite.getGlobalBounds().height) )
        {
            offsetX = moveEvent.x - itr->sprite.getPosition().x;
            offsetY = moveEvent.y - itr->sprite.getPosition().y;

            // Moving the cursor if the mouse button is held down
            if (buttonEvent.button == sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                itr->sprite.setPosition(moveEvent.x + offsetX, moveEvent.y + offsetY);
            else if (buttonEvent.button == sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
                tooltips.erase(itr);
        }
    }
}

// Method to add a new tooltip to the tooltip list
void UserInterface::addTooltip(std::string header, std::string body, sf::Texture& texture, int x, int y)
{
    // Temporary object to store the values in
    Tooltip tempTooltip;

    // Creating the header text
    tempTooltip.headerText.setString(header);
    tempTooltip.headerText.setFont(regularFont);
    tempTooltip.headerText.setPosition(x + 5, y + 1);
    tempTooltip.headerText.setScale(.75f, .75f);

    // Creating the body text
    tempTooltip.bodyText.setString(body);
    tempTooltip.bodyText.setFont(regularFont);
    tempTooltip.bodyText.setPosition(x + 12, y + 25);
    tempTooltip.bodyText.setScale(.75f, .75f);

    tempTooltip.sprite.setTexture(texture);
    tempTooltip.sprite.setPosition(x, y);
    tempTooltip.isCloseable = true;
    tempTooltip.isMoveable = true;
    tempTooltip.sprite.scale(0.5f, 0.5f);

    // Adding the temporary object to the tooltip list
    tooltips.push_back(tempTooltip);
}

void UserInterface::nextDialogueLine() { dialogueBox.nextLine(); }

// Method to add a new dialogue box. Normally only one of these is needed at a time.
void UserInterface::addDialogueBox(std::string scriptPath, sf::Texture& image, int x, int y)
{
    if(dialogueBox.openScript(scriptPath))
    {
        std::cout << "script loaded successfully." << std::endl;
        dialogueBox.sprite.setPosition(x, y);
        dialogueBox.sprite.setTexture(image);
        dialogueBox.name.setFont(regularFont);
        dialogueBox.name.setCharacterSize(48);
        dialogueBox.dialogue.setFont(regularFont);
        dialogueBox.dialogue.setCharacterSize(48);
        dialogueBox.nextLine();
    }
}

// Method to draw the various UI elements to the screen
void UserInterface::draw(sf::RenderWindow *window)
{
	for (auto i = highlights.begin(); i != highlights.end(); i++)
		i->draw(window);

    for (auto i = tooltips.begin(); i != tooltips.end(); i++)
        i->draw(window);

    //dialogueBox.draw(window);
}

// Method to get the tooltip list
std::list<Tooltip> UserInterface::getTooltips() { return tooltips; }

// Method to return a specific tooltip based on it's header
Tooltip UserInterface::getTooltip(std::string header)
{
    std::list<Tooltip>::iterator i;
    for (i = tooltips.begin(); i != tooltips.end(); i++)
        if (i->headerText.getString() == header)
            return *i;

    std::cout << "Tooltip with header '" << header << "'could not be found." << std::endl;
    return Tooltip();
}

// Method to return a specific tooltip based on the mouse pointer
Tooltip UserInterface::getTooltip(int mouseX, int mouseY)
{
    std::list<Tooltip>::iterator i;
    for (i = tooltips.begin(); i != tooltips.end(); i++)
        if (i->sprite.getGlobalBounds().contains(mouseX, mouseY))
            return *i;

    std::cout << "Tooltip at (" << mouseX << "," << mouseY << ") could not be found." << std::endl;
    return Tooltip();
}

void UserInterface::highlightTiles(std::vector<sf::Vector2i> highlightRange, sf::Color colour, int tileSize)
{
	for(auto itr = highlightRange.begin(); itr != highlightRange.end(); ++itr)
	{
		highlights.push_back(TileHighlight(itr->x, itr->y, colour, tileSize));
	}
}

void UserInterface::highlightTiles(std::vector<sf::Vector3i> highlightRange, sf::Color colour, int tileSize)
{
	std::cout << "Highlighting " << highlightRange.size() << " tiles!" << std::endl;
	for(auto itr = highlightRange.begin(); itr != highlightRange.end(); ++itr)
	{
		highlights.push_back(TileHighlight(itr->x, itr->y, colour, tileSize));
	}
}

void UserInterface::highlightTiles(std::stack<sf::Vector2i> highlightRange, sf::Color colour, int tileSize)
{
	while(!highlightRange.empty())
	{
		sf::Vector2i& current = highlightRange.top();
		highlights.push_back(TileHighlight(current.x, current.y, colour, tileSize));
		highlightRange.pop();
	}
}
