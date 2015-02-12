#include "Item.h"

Item::Item(std::string name, std::string weaponType, int maxUses, int remainingUses, bool foeTarget, int hit, int crit, int might, int range, int excludedRange, int damageType)
{
    // Calling the init function to initilize properties shared by both weapons
    // and items.
    init(name, maxUses, remainingUses, foeTarget, range);

    properties["hitChance"] = hit;
    properties["critChance"] = crit;
    properties["might"] = might;
    properties["excludedRange"] = excludedRange;

    if(damageType == 0 || damageType == 1)
        properties["damageType"] = damageType;
    else properties["damageType"] = -1;

    properties["isWeapon"] = 1;
    wpnType = weaponType;
}

Item::Item(std::string name, int maxUses, int remainingUses, bool foeTarget, int modifier, int targetStat, int range)
{
    // Calling the init function to initilize properties shared by both weapons
    // and items.
    init(name, maxUses, remainingUses, range, foeTarget);

    properties["modifier"] = modifier;
    properties["targetStat"] = targetStat;
    properties["isWeapon"] = 0;
}

void Item::init(std::string name, int maxUses, int remainingUses, int range, bool foeTarget)
{
    itemName = name;
    wpnType = "";

    properties["maxUses"] = maxUses;
    properties["remainingUses"] = remainingUses;
    properties["range"] = range;
    targetFoe = foeTarget;
}

int Item::getProperty(std::string key)
{
    return properties[key];
}

std::string Item::getName() { return itemName; }
std::string Item::getType() { return wpnType; }
bool Item::targetsFoe() { return targetFoe; }
