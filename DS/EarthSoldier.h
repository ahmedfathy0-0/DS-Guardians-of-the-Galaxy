#pragma once
#include "Unit.h"

class EarthSoldier : public Unit
{
public:
	EarthSoldier(int id, int jointime, double health, double power, int attackcapacity);
	void attack(Unit* target) override;
};

