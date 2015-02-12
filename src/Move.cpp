#include "Move.h"

Move::Move(int _range, int _damage, bool _targetAllies)
{
    range = _range;
    damage = _damage;
    targetAllies = _targetAllies;
    manipStat = "";
    manipValue = 0;
}

Move::Move(int _range, int _damage, bool _targetAllies, std::string _manipStat, int _manipValue)
{
    range = _range;
    damage = _damage;
    targetAllies = _targetAllies;
    manipStat = _manipStat;
    manipValue = _manipValue;
}

void Move::Manipulate(Unit* target)
{
    target->modifyStat("defense", -1);
}
Move::~Move()
{
    //dtor
}
