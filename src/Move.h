// This class is used to define unit moves in the game.
// Moves are special abilities that either deal damage to enemies or heal allies
// Moves can also buff or debuff other units

#ifndef MOVE_H
#define MOVE_H
#include <string>
#include "Unit.h"

class Move
{
    public:
        Move(int _range, int _damage, bool _targetAllies);
        Move(int _range, int _damage, bool _targetAllies, std::string _manipStat, int _manipValue);
        virtual ~Move();
        void Manipulate(Unit* target);  // Used to manipulate the stats of a target unit.
    protected:
    private:
        int range;  // The move's range in tiles. If the range is zero the move can only be used on the caster
        int damage; // How  much damage the move does, if this value is negative the move will heal a unit
        bool targetAllies;  // If this move can target allies or enemies.
        std::string manipStat;   // The stat to manipulate
        int manipValue;     // The value to manipluate the stat by
};

#endif // MOVE_H
