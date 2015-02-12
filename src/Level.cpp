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
    //combatController = AI(unitPath, "classStats/");
    std::cout << "AI initilized" << std::endl;

    imageManager.loadImage(spritesheetPath + "/mage.png", "mageSprite");
    imageManager.loadImage(spritesheetPath + "/warrior.png", "warriorSprite");
    imageManager.loadImage(spritesheetPath + "/tank.png", "tankSprite");

    //combatController.initSprites(imageManager);
}

// Method to call the AI's update methods.
void Level::updateAI(std::list<Unit> enemies)
{
    // Iterator for iteratin'
    std::list<Unit>::iterator unit_itr;

    std::cout << "updating the AI" << std::endl;

    // Updating the enemy unit list, in case any of the units died during the last turn.
    //combatController.setEnemyUnits(enemies);
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

    // Drawing the units
/*    for(cUnitItr = combatController.getAvailableUnits().begin();
        cUnitItr != combatController.getAvailableUnits().end();
        ++cUnitItr)
    {
        window.draw(cUnitItr->getSprite());
    }*/
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
