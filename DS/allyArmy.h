#ifndef ALLY_ARMY_H 
#define ALLY_ARMY_H
#include "Army.h"

class allyArmy : public Army
{
    LinkedQueue<Unit*> saverUnitsList;
    Unit* allyUnit;
    Unit* SU_attack;
    LinkedQueue<Unit*>* SU_attacking_list;

public:
    allyArmy(Game* pGame);
    bool attack(Army* enemy, int timestep);
    void Withdrawal();
    void addUnit(Unit*);
    Unit* removeUnit(string type);
    int getSoldiersCount();
    void printArmy();
    void printFightingUnits();
    void Armyfile(fstream&, int, int, int, int, int,int);
};

#endif