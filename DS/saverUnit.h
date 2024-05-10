#pragma once
#include "Unit.h"
class saverUnit :
    public Unit
{
public:
    saverUnit(int id, int jointime, double health, double power, int attackcapacity);
    void attack(LinkedQueue <Unit*>* enemyTemp, int timestep, Game* pGame, Army* enemy) override;
};

