#pragma once
#include "Army.h"
#include "AlienDrone.h"
#include "AlienMonster.h"
#include "AlienSoldier.h"

class AlienArmy : public Army
{

	LinkedQueue<AlienSoldier> aSoldiersList;
	AlienMonster* aMonstersList;
	DoubleEndedQueue<AlienDrone> aDronesList;

};

