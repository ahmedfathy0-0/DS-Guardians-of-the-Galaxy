#pragma once
#include "Unit.h"

class AlienMonster : public Unit
{

public:
	void attack(Unit* target) override;
};

