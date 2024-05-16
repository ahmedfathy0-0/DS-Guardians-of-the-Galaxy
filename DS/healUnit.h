#pragma once
#include "Unit.h"
class healUnit :
    public Unit
{


    bool doneHealing;
    LinkedQueue<Unit*> tempList;

public:

    // constructor
    healUnit(int id, int jointime, double health, double power, int attackcapacity);

    // battle related functions
    void attack(LinkedQueue <Unit*>* SoldierTemp, int timestep, Game* pGame, Army* enemy) override;
    void heal(Unit* unitToHeal);

    // getters 
    LinkedQueue<Unit*>* getTempList();

};

