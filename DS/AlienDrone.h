#ifndef ALIEN_DRONE_H
#define ALIEN_DRONE_H
// !ALIEN_DRONE_H

#include "Unit.h"

class AlienDrone : public Unit
{

public:
	AlienDrone(int id, int jointime, double health, double power, int attackcapacity);
	void attack(Unit* target) override;
};

#endif