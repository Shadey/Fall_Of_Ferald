#include "Level.h"
#include <sstream>
#include <iostream>
#include "Unit.h"

Level::Level(const std::string& mapPath, const std::string& tileSheetPath, ImageManager* imageManager)
{
    std::ifstream inFile(mapPath);
    std::istringstream subString;
    std::string line;
    imageManager->loadImage(tileSheetPath);
    levelWidth = 0;
    levelHeight = 0;
	playerTurn = true;
	playerUnitSelected = false;
	hoveredTile = sf::Vector2i(0,0);
	selectedUnitPos = sf::Vector2i(-1,-1);
	previouslyHoveredTile = sf::Vector2i(-1,-1);
	selectedUnit = NULL;

    std::cout << "loading level" << std::endl;

    if(inFile.good())
    {
        int i = 0;      // Iterator for within the lines of text
        int j  = -1;    // Iterator for the lines themselves, initially -1 so
                        // we can load the map from the second line.
        while(std::getline(inFile, line))
        {
            subString.str(line);
            if(j == -1)
            {
                std::string ss;
                while(std::getline(subString, ss, ','))
                {
                    std::cout << "paring the first line" << std::endl;

                    // If statments are there to prevent cleaning up the converter
                    // as doing so requires multiple function calls.
                    if(levelHeight == 0 && levelWidth != 0)
                    {
                        std::istringstream convert(ss);
                        convert >> levelHeight;
                    }

                    if(levelWidth == 0)
                    {
                        std::istringstream convert(ss);
                        convert >> levelWidth;
                    }

                }

                std::cout << "Level defined with size " << levelWidth << "x" << levelHeight << std::endl;

                // Defining the array
                tiles = new Tile*[levelWidth];
                for(int k = 0; k < levelWidth; ++k)
                    tiles[k] = new Tile[levelHeight];
            }
            else if (j < levelHeight)
            {
                char id;
                while (i < levelWidth)
                {
                    // Grabbing a character from the line string
                    id = subString.get();

                    int identifier = id - '0';
                    tiles[i][j] = Tile(identifier, imageManager->getTexture(tileSheetPath));
                    tiles[i][j].sprite.setPosition(i * tileSize, j * tileSize);
                    i++;
                }
                i = 0;  // Line parsed, moving back to the start
            }
            // Line parsed, move to the next line
            j++;

            // Clearing up the subString
            subString.str("");
            subString.clear();
        }
    }
    else
    {
        std::cout << "Error loading " << mapPath << ", file not found." << std::endl;
    }
}

// Method to initilize the AI. Seperate from the constructor on the off chance that there is a level
// with no enemies or NPC allies.
void Level::initilizeAI(const std::string& unitPath, const std::string& spritesheetPath, ImageManager& imageManager)
{
    std::cout << "starting to init AI" << std::endl;
    combatController = AI(unitPath, "Stats/");
    std::cout << "AI initilized" << std::endl;

	// Loading the images for the NPC units
    imageManager.loadImage(spritesheetPath + "/mage.png", "mage");
    imageManager.loadImage(spritesheetPath + "/warrior.png", "warrior");
    imageManager.loadImage(spritesheetPath + "/tank.png", "tank");
	imageManager.loadImage(spritesheetPath + "/player.png", "player");

	// Setting the sprites for the NPC units, works as long as the generic unit
	// names are the same as the imageManager keys
	for(auto &unit : combatController.getAvailableUnits())
		unit.setSprite(imageManager.getTexture(unit.getType()));

	// Adding a unit for the AI to fight, normally these would be loaded from a file but eh.
	combatController.addEnemyUnit(Unit("test", "tank", 5, 50, 10, 0, 6, 3, 16, 2, 3, 3, 1, 3));
	combatController.getEnemyUnits().back().setSprite(imageManager.getTexture("player"));

	// Initilising the pathfinder
	pathfinder = Pathfinder(this);
}

void Level::update(InputManager& inputManager, UserInterface& ui)
{
	// Updating the sprites
	combatController.updateSprites(tileSize);
	sf::Vector2i mousePos = inputManager.getMousePosition();
	//selectedUnit = NULL;

	if(!playerTurn)
	{
		updateAI();
		nextTurn();
	}
	else
	{
		// Checking if the AI's turn has been initiated
		if(inputManager.pressedOnce("nextTurn"))
			//nextTurn();
		combatController.outputPositions();

		// Finding the tile that the cursor is hovered over
		hoveredTile = sf::Vector2i(mousePos.x / tileSize, mousePos.y / tileSize);

		// Displaying a unit's range if the player's unit is clicked for the first time
		if(inputManager.pressedOnce(sf::Mouse::Button::Left))
		{
			ui.clearHighlight();
			playerUnitSelected = false;

			// Checking each unit to see if we've clicked it
			for(auto &unit : combatController.getEnemyUnits())
			{
				if(hoveredTile.x == unit.getX() && hoveredTile.y == unit.getY())
				{

					toHighlight = pathfinder.calculateArea(sf::Vector2i(unit.getX(), unit.getY()),
						unit.getStat("moveRange"));

					ui.highlightTiles(toHighlight, ui.friendlyHighlight, tileSize);
					playerUnitSelected = true;
					selectedUnitPos = sf::Vector2i(unit.getX(), unit.getY());
					selectedUnit = &unit;

					// No need to check the rest of the units
					break;
				}
			}

			// Moving the selected unit, if we didn't select it this frame
			if(selectedUnit != NULL && !playerUnitSelected)
			{
				bool changeTurn = true;

				// Only move the unit if it hasn't been moved this turn
				if(!selectedUnit->getMoved())
				{
				// Only moving within the moverange
					for(auto &tile : toHighlight)
					{
						if(hoveredTile.x == tile.x && hoveredTile.y == tile.y)
						{
							selectedUnit->setPosition(hoveredTile.x, hoveredTile.y, tileSize);
							break;
						}
					}
				}
				selectedUnit->setMoved(true);
				selectedUnit = NULL;

				// Changing turn if all the player units have been used
				for(auto &unit : combatController.getEnemyUnits())
				{
					if(!unit.getMoved())
						changeTurn = false;
				}

				if(changeTurn)
					nextTurn();
			}
		}

		// Drawing the path between the selected unit and the mouse
		if(playerUnitSelected && hoveredTile != previouslyHoveredTile)
		{
			bool validTile = false;

			// Checking if the hovered tile in our range
			for(auto &i : toHighlight)
			{
				if(i.x == hoveredTile.x && i.y == hoveredTile.y)
					validTile = true;
			}

			if(validTile)
			{
				std::stack<sf::Vector2i> pathStack;
				pathStack = pathfinder.getPath(toHighlight, selectedUnitPos, hoveredTile);
				ui.clearHighlight(ui.enemyHighlight);

				ui.highlightTiles(pathStack, ui.enemyHighlight, tileSize);
			}
		}

		// Updating the previous hovered tile
		previouslyHoveredTile = hoveredTile;
	}
}

// Method to call the AI's update methods.
void Level::updateAI()
{
	for(auto &unit : combatController.getAvailableUnits())
	{
		std::list<Unit*> possibleTargets;		// What the AI controlled unit can attack
		std::vector<sf::Vector3i> moveRange;	// Where the AI controlled unit can move to

		// Finding the moveRange
		moveRange = pathfinder.calculateArea(sf::Vector2i(unit.getX(), unit.getY()), unit.getStat("moveRange"));

		// Searching for possible targets based on the moveRange
		possibleTargets = combatController.getPossibleTargets(moveRange);

		// If there were valid targets within the unit's attack range
		if(possibleTargets.size() != 0)
		{
			Unit* target = combatController.selectTarget(possibleTargets, unit);

			// Ensuring that target isn't null, it shouldn't be but it doesn't hurt to check
			if(target != NULL)
			{
				// Where the AI can attack the target from on the map
				std::vector<sf::Vector3i> validPositions;
				std::vector<sf::Vector3i> tempPositions;

				// calculateArea breaks if the pos vector is constructed in the function call. No idea why.
				sf::Vector2i pos(target->getX(), target->getY());
				tempPositions = pathfinder.calculateArea(pos, 1); // Using 1 'till weapons are done

				std::cout << std::endl << unit.getType() << " attacking !" << std::endl;

				// Finding the valid positions
				for(auto &outer : moveRange)
				{
					for(auto &inner : tempPositions)
					{
						if(outer.x == inner.x && outer.y == inner.y)
						{
							int x = inner.x;
							int y = inner.y;
							validPositions.push_back(sf::Vector3i(x, y, tiles[x][y].terrainDef));
						}
					}
				}

				// TODO
				// Preventing units moving onto the same tile
				// It's not working ;_;
/*
				for(auto &itr : combatController.getAvailableUnits())
				{
					if(itr.getX() != unit.getX() && itr.getY() != unit.getY())
					{
						for(auto posItr = validPositions.begin(); posItr != validPositions.end() ; )
						{
							if(posItr->x == itr.getX() && posItr->y == itr.getY())
								posItr = validPositions.erase(posItr);
							else ++posItr;
						}
					}
				}
				for(auto &itr : combatController.getEnemyUnits())
				{
					if(itr.getX() == unit.getX() && itr.getY() == unit.getY())
					{
						for(auto posItr = validPositions.begin(); posItr != validPositions.end() ; )
						{
							if(posItr->x == itr.getX() && posItr->y == itr.getY())
								posItr = validPositions.erase(posItr);
							else ++posItr;
						}
					}
				}
*/
				// Selecting the best tile to attack from
				if(validPositions.size() != 0)	// Only move if there's a valid position
				{
					sf::Vector2f bestPosition = combatController.selectPosition(validPositions);
					unit.setPosition(bestPosition, tileSize);
				}

				// Attacking the target
				target->modifyStat("health", 10);	// 10 is a temp value until weapons are redone
				std::cout << "The target's health is " << target->getStat("health") << std::endl;
			}

			// Updating the unit's sprite
			unit.getSprite().setPosition(unit.getX() * tileSize, unit.getY() * tileSize);

			// Actual attacking should go here
		}
	}

}

// Draw method, draws the tiles and the AI-controlled units
void Level::draw(sf::RenderWindow& window)
{
    // Unit iterator
    std::list<Unit>::iterator cUnitItr;

    // Drawing the tiles
    for(int i = 0; i < levelWidth; i++)
    {
        for(int j = 0; j < levelHeight; j++)
        {
            window.draw(tiles[i][j].getSprite());
        }
    }

	// Drawing the units enemy
	for(auto &unit : combatController.getAvailableUnits())
		window.draw(unit.getSprite());

	// Drawing the player units
	for(auto &unit : combatController.getEnemyUnits())
		window.draw(unit.getSprite());
}

std::string Level::getTileType(int x, int y)
{
    // Preventing horrible things from happening
    if(x < levelWidth && y < levelHeight && x >= 0 && y >= 0)
    {
        return tiles[x][y].getType();
    }
    else
    {
        // Tile specified doesn't exist, returning a large value so that the
        // tile is ignored by the pathfinder.
        return "wall";
    }
}

void Level::nextTurn()
{
	if(playerTurn)
	{
		playerTurn = false;
		for(auto &unit : combatController.getAvailableUnits())
			unit.setMoved(false);
	}
	else
	{
		playerTurn = true;
		for(auto &unit : combatController.getEnemyUnits())
			unit.setMoved(false);
	}
}

Tile Level::getTile(int x, int y) {return tiles[x][y];}
int Level::getMapSizeX(){ return levelWidth; }
int Level::getMapSizeY(){ return levelHeight; }

Level::~Level()
{
    // Clearing up the tile array
    for(int i = 0; i < levelWidth; ++i)
        delete[] tiles[i];
    delete tiles;

}
