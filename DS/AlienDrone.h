#pragma once
#include "Unit.h"

class AlienDrone : public Unit
{

public:

	void attack(Unit* target) override;
};

