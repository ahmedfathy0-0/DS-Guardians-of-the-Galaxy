#pragma once
#include "Unit.h"

class AlienSoldier : public Unit
{

public:
	void attack(Unit* target) override;
};

