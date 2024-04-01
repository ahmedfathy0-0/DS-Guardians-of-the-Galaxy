#pragma once
#include "Unit.h"
class EarthGunnery : public Unit
{

public:
	void attack(Unit* target) override;
};

