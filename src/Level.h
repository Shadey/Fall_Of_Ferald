// The level class is responsible for managing each individual level.
// This includes Units and Tiles

#ifndef LEVEL_H
#define LEVEL_H
#include <string>
#include <fstream>
#include "Tile.h"
#include "ImageManager.h"
#include "AI.h"
#include <SFML/Graphics.hpp>


class Level
{
    public:
        Level(const std::string& mapPath, const std::string& tilesheetPath, ImageManager* imageManager);
        void initilizeAI(const std::string& unitPath, const std::string& spritesheetPath, ImageManager& imageManager);
        void draw(sf::RenderWindow& window);
		void update();
        virtual ~Level();
        Tile getTile(int x, int y);
        std::string getTileType(int x, int y);
        int getMapSizeX();
        int getMapSizeY();
		inline int getTileSize() { return tileSize; }
		inline AI& getAI() { return combatController; }
		
		inline void nextTurn() { if(playerTurn) playerTurn = false; else playerTurn = true; }
		inline bool isPlayerTurn() { return playerTurn; }
    private:
        int levelWidth;
        int levelHeight;
        const int tileSize = 64;
		bool playerTurn;
        Tile** tiles;
        AI combatController;

		// Private functions
        void updateAI();
};

#endif // LEVEL_H
