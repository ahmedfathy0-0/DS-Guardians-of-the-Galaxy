#pragma once
#include "Unit.h"

class EarthSoldier : public Unit
{

public:
	void attack(Unit* target) override;
};

