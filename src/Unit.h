#ifndef UNIT_H
#define UNIT_H

#include "Actor.h"
#include "ImageManager.h"
#include "Item.h"
#include <string>
#include <list>
#include <array>


class Unit : public Actor
{
    friend class UnitManager;
    public:
        Unit(std::string unitName, std::string unitType, int health, int speed, int skill, int strength, int defense, int moveRange, int _x, int _y, int _layer);
        Unit(std::string unitType, int _x, int _y, int _layer, int statArray[], int lvl);
        virtual ~Unit();
        void modifyStat(std::string statName, int mod);
        void setSprite(ImageManager imageManager, const std::string& filename, int x, int y, int w, int h);
        void setSprite(sf::Texture& texture, int sourceX, int sourceY, int sourceW, int sourceH);
        bool selectWeapon(int pos);
        std::list<Item> getWeapons();
        Item& getCurrentWeapon();
        int getStat(std::string statName);
        std::string getHighestStat();
        std::string getType();
        int getX(const int tileSize);
        int getY(const int tileSize);
        int getX(){return x;}
        int getY(){return y;}
        int getMaxRange();

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
        std::string movementType;   // The unit's movement type. (Treads, flight etc.)
        std::string type;           // The unit's type (Tank, Mech, Infantry etc.)
        std::string name;           // The unit's name (if not specified, this becomes the unit's type)
        int level;

        // The unit's stats, stored in a map so that individual stats can be easily accessed.
        std::map<std::string, Stat> stats;
        int x, y;                   // The unit's x and y coords on the map
        std::list<Item> inventory;
        std::list<Item>::iterator currentWeapon;
};

#endif // UNIT_H
