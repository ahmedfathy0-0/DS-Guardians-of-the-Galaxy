#pragma once
#include "Unit.h"


class AlienSoldier : public Unit
{

public:
	AlienSoldier(int id, int jointime, double health, double power, int attackcapacity);
	void attack(LinkedQueue <Unit*>* SoldierTemp, int timestep, Game* pGame, Army* enemy) override;
};

