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

void UserInterface::update(sf::Vector2i pointerPosition, sf::Vector2i prevPointerPos, bool lmbPressed, bool rmbPressed)
{
    int offsetX, offsetY;       // The x and y offset to move the tooltip by

	// If the LMB is _held_ not pressed
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		for(auto itr = tooltips.begin(); itr != tooltips.end(); ++itr)
		{
			if(itr->containsPoint(pointerPosition))
			{
				offsetX = pointerPosition.x - prevPointerPos.x;
				offsetY = pointerPosition.y - prevPointerPos.y;
				itr->sprite.move(offsetX, offsetY);
				itr->headerText.move(offsetX, offsetY);
				itr->bodyText.move(offsetX, offsetY);
				break;
			}
		}

		if(lmbPressed)
			dialogueBox.nextLine();
	}
	else if (rmbPressed)
	{
		for(auto itr = tooltips.begin(); itr != tooltips.end(); )
		{
			if(itr->containsPoint(pointerPosition))
			{
				itr = tooltips.erase(itr);
				break;
			}
			else ++itr;
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
		dialogueBox.active = true;
    }
}

// Method to draw the various UI elements to the screen
void UserInterface::draw(sf::RenderWindow *window)
{
	for (auto i = highlights.begin(); i != highlights.end(); i++)
		i->draw(window);

    for (auto i = tooltips.begin(); i != tooltips.end(); i++)
        i->draw(window);

    dialogueBox.draw(window);
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

// Clearing highlights of a certain colour
void UserInterface::clearHighlight(sf::Color colour)
{
	//for(int i = 0; i < highlights.size() ; )
	for(auto i = highlights.begin(); i != highlights.end() ; )
	{
		if(i->getColour() == colour)
			highlights.erase(i);
		else i++;
	}
}

