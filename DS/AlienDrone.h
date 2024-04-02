#pragma once
#include "Unit.h"

class AlienDrone : public Unit
{

public:
	AlienDrone(int id, int jointime, double health, double power, int attackcapacity);
	void attack(Unit* target) override;
};

