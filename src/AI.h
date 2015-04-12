/* The AI class is responsible for determining the decisions that should be
 * made by the computer in a combat scenario. It does so by populating a list
 * of enemy units at the start of each of it's turns. It then checks whether
 * or not any of it's units can engage with the enemy.
 * if they can, the AI determine's a target using a heuristic and attacks it.
 * If not, the unit does nothing
 */

#ifndef AI_H
#define AI_H
#include <list>
#include <vector>
#include <map>
#include <SFML/System/Vector3.hpp>
#include "Unit.h"
#include "Tile.h"

class AI
{
    public:
        AI();
        AI(const std::string l_unitsPath, const std::string l_statsPath);
		bool parseFile(const std::string fileLocation, bool gettingGrowthRates);
        std::list<Unit> getPossibleTargets(Unit& currentUnit, Tile** const levelMap);
        void setMapDimensions(int width, int height);
		inline void addEnemyUnit(Unit unit) { enemyUnits.push_back(unit); }
        virtual ~AI();

		// Accessor methods
		inline std::list<Unit>& getAvailableUnits() { return availableUnits; }
		inline std::list<Unit>& getEnemyUnits() { return enemyUnits; }
    private:
        std::list<Unit> availableUnits;	// The units that are available to this AI
        std::list<Unit> enemyUnits;		// The units that are available to an enemy faction ie player.
        static const int statCount = 9; // The number of stats a unit has
        int mapWidth;
        int mapHeight;

        void calculateCosts(Unit& currentUnit, int** costs, Tile** const levelMap);
};

#endif // AI_H
