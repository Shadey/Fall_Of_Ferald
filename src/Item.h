#ifndef ITEM_H
#define ITEM_H
#include <map>
#include <string>

class Item
{
public:
    Item(std::string name, std::string weaponType, int maxUses, int remainingUses, bool foeTarget, int hit, int crit, int might, int range, int excludedRange, int damageType);
    Item(std::string name, int maxUses, int remainingUses, bool foeTarget, int modifier, int targetStat, int range);
    std::string getName();
    std::string getType();
    bool targetsFoe();
    int getProperty(std::string key);
private:
    void init(std::string name, int maxUses, int remainingUses, int range, bool foeTarget);

    std::map<std::string, int> properties;  // Map to store properties of the item
    std::string itemName;   // The name of the item
    std::string wpnType;    // The type of weapon. Only used if the item is a weapon
    bool targetFoe; // Determines wether or not the item can be used on friendlies or foes
};
#endif // ITEM_H
