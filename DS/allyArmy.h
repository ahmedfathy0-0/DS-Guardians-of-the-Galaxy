#pragma once
#include "Army.h"

class allyArmy :
    public Army
{
    LinkedQueue<Unit*> saverUnitsList;
    Unit* allyUnit;
    Unit* SU_attack;
    LinkedQueue<Unit*>* SU_attacking_list;

public:
    allyArmy(Game* pGame);
    void attack(Army* enemy, int timestep);
    void addUnit(Unit*);
    Unit* removeUnit(string type);
    int getSoldiersCount();
    void printArmy();
    void printFightingUnits();
    void Armyfile(fstream&, int, int, int, int, int);
};

