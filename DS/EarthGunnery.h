#pragma once
#include "Unit.h"
class EarthGunnery : public Unit
{

public:
	EarthGunnery(int id, int jointime, double health, double power, int attackcapacity);
	void attack(Unit* target) override;
};

