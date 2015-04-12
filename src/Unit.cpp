#include "Unit.h"

// Constructor
Unit::Unit(std::string unitName, std::string unitType, int lvl, int health, int strength, int magic, int skill,
	int speed, int defense, int resistance, int luck, int moveRange, int _x, int _y)
{
	level = lvl;

    // Initilizing the unit's stats
    stats["health"] = Stat(health);
    stats["strength"] = Stat(strength);
	stats["magic"] = Stat(magic);
    stats["skill"] = Stat(skill);
    stats["speed"] = Stat(speed);
    stats["defense"] = Stat(defense);
	stats["resistance"] = Stat(resistance);
	stats["luck"] = Stat(luck);
    stats["moveRange"] = Stat(moveRange);

    if (unitName == "")
        name = unitType;
    else name = unitName;

	x = _x;
	y = _y;
}

// Alternative constructor for a generic unit, takes an array
Unit::Unit(std::string unitType, int _x, int _y, int* statArray, int lvl)
{
    // Naming the unit based on it's type.
    name = unitType;
    type = unitType;

    // Setting the unit's level
    level = lvl;

    stats["health"]     = Stat(statArray[0]);
    stats["strength"]   = Stat(statArray[1]);
    stats["magic"]      = Stat(statArray[2]);
    stats["skill"]      = Stat(statArray[3]);
    stats["speed"]      = Stat(statArray[4]);
    stats["defense"]    = Stat(statArray[5]);
    stats["resistance"] = Stat(statArray[6]);
    stats["luck"]       = Stat(statArray[7]);
    stats["moveRange"]  = Stat(statArray[8]);

	x = _x;
	y = _y;
}

std::list<Item> Unit::getWeapons()
{
    std::list<Item> value;

    for(auto i : inventory)
    {
        if(i.getProperty("isWeapon") == 1)
            value.push_back(i);
    }

    return value;
}

Unit::~Unit()
{
    //dtor
}

void Unit::modifyStat(std::string statName, int mod)
{
    // Ensuring that the unit cannot be healed over it's max health
    if(statName == "health" && mod < 0)   // if the modifier is less than zero, healing is occuring.
    {
        if (stats[statName].getCurrent() + mod < stats[statName].base)
            stats[statName].modifier += mod;
        else
            stats[statName].modifier = 0;
    }
    else
    {
        stats[statName].modifier += mod;
    }
}

bool Unit::selectWeapon(int pos)
{
    std::list<Item>::iterator item_itr = inventory.begin();
    std::advance(item_itr, pos);

    if(item_itr->getProperty("isWeapon"))
    {
        currentWeapon = item_itr;
        return true;
    }
    else
    {
        return false;
    }
}

std::string Unit::getHighestStat()
{
    std::map<std::string, Stat>::iterator stat_itr;
    std::string highestName;
    int highestVal = 0;

    for(stat_itr = stats.begin(); stat_itr != stats.end(); ++stat_itr)
    {
        if((stat_itr->second.getCurrent() < highestVal)
           && (stat_itr->first == "magic" || stat_itr->first == "strength" || stat_itr->first == "defense"))
        {
            highestVal = stat_itr->second.getCurrent();
            highestName = stat_itr->first;
        }
    }
    return highestName;
}

std::string Unit::getType()
{
    return type;
}

int Unit::getStat(std::string statName)
{
    return stats[statName].getCurrent();
}

Item& Unit::getCurrentWeapon()
{
    return *currentWeapon;
}

int Unit::getMaxRange()
{
    std::list<Item>::iterator item_itr;
    int maxRange = 0;

    for(item_itr = inventory.begin(); item_itr != inventory.end(); ++item_itr)
    {
        if(item_itr->getProperty("isWeapon"))
        {
            if(item_itr->getProperty("range") > maxRange)
                maxRange = item_itr->getProperty("range");
        }
    }

    return maxRange;
}
