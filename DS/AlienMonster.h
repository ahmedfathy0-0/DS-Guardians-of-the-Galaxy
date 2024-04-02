#pragma once
#include "Unit.h"

class AlienMonster : public Unit
{

public:
	AlienMonster(int id, int jointime, double health, double power, int attackcapacity);

	void attack(Unit* target) override;
};

