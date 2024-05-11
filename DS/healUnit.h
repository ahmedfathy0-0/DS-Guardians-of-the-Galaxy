#pragma once
#include "Unit.h"
class healUnit :
    public Unit
{

    bool doneHealing;
    LinkedQueue<Unit*> tempList;

public:
    healUnit(int id, int jointime, double health, double power, int attackcapacity);
    void attack(LinkedQueue <Unit*>* SoldierTemp, int timestep, Game* pGame, Army* enemy) override;
    void heal(Unit* unitToHeal);
    LinkedQueue<Unit*>* getTempList();

};

