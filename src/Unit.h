#ifndef UNIT_H
#define UNIT_H
#include "ImageManager.h"
#include "Item.h"
#include <string>
#include <list>
#include <SFML/Graphics/Sprite.hpp>


class Unit
{
    friend class UnitManager;
    public:
		Unit(std::string unitName, std::string unitType, int lvl, int health, int strength, int magic, int skill,
			int speed, int defense, int resistance, int luck, int moveRange, int _x, int _y);
        Unit(std::string unitType, int _x, int _y, int* statArray, int lvl);
        virtual ~Unit();
        void modifyStat(std::string statName, int mod);
		inline void setSprite(sf::Texture& texture) { sprite.setTexture(texture); }
        bool selectWeapon(int pos);
        std::list<Item> getWeapons();
        Item& getCurrentWeapon();
        int getStat(std::string statName);
        std::string getHighestStat();
        std::string getType();
        int getX(){return x;}
        int getY(){return y;}
        int getMaxRange();
		inline sf::Sprite& getSprite() { return sprite; }

        // Structure used to store unit statisitics and modifiers
        struct Stat
        {
            Stat(int _base)
            {
                base = _base;
                modifier = 0;
            }
            Stat()
            {
                base = 0;
                modifier = 0;
            }
            int getCurrent() { return base - modifier; }
            int base;           // The base stat
            int modifier;       // The modifier to be applied to the stat
        };

    private:
		sf::Sprite sprite;
        std::string movementType;   // The unit's movement type. (Treads, flight etc.)
        std::string type;           // The unit's type (Tank, Mech, Infantry etc.)
        std::string name;           // The unit's name (if not specified, this becomes the unit's type)
        int level;

        // The unit's stats, stored in a map so that individual stats can be easily accessed.
        std::map<std::string, Stat> stats;
        int x, y;                   // The unit's x and y coords on the map
		int tileSize;
        std::list<Item> inventory;
        std::list<Item>::iterator currentWeapon;
};

#endif // UNIT_H
