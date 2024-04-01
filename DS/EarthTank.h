#pragma once
#include "Unit.h"

class EarthTank : public Unit
{

public:
	void attack(Unit* target) override;
};

