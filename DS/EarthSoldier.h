#pragma once
#include "Unit.h"

class EarthSoldier : public Unit
{
public:
	EarthSoldier(int id, int jointime, double health, double power, int attackcapacity);
	void attack(LinkedQueue <Unit*>* SoldierTemp, int timestep, Game* pGame, Army* enemy) override;
};

