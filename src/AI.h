/* The AI class is responsible for determining the decisions that should be
 * made by the computer in a combat scenario. It does so by populating a list
 * of enemy units at the start of each of it's turns. It then checks whether
 * or not any of it's units can engage with the enemy.
 * if they can, the AI determine's a target using a heuristic and attacks it'sb_type
 * target. If not, the AI will move its unit towards the nearest enemy unit.
 */

#ifndef AI_H
#define AI_H
#include <list>
#include <map>
#include <SFML/System/Vector3.hpp>
#include "Unit.h"
#include "Tile.h"

class AI
{
    public:
        AI();
        AI(const std::string l_unitsPath, const std::string l_statsPath);
        void loadStats(const std::string statsPath);
        std::list<Unit> getPossibleTargets(Unit& currentUnit, Tile** const levelMap);
        void setMapDimensions(int width, int height);
        virtual ~AI();
    private:
        std::list<Unit> availableUnits;	// The units that are available to this AI
        std::list<Unit> enemyUnits;		// The units that are available to an enemy faction ie player.
        std::map<std::string, int**> statInfo;
        const int statCount = 8;        // The number of stats a unit has
        int mapWidth;
        int mapHeight;

        void calculateCosts(Unit& currentUnit, int** costs, Tile** const levelMap);
};

#endif // AI_H
