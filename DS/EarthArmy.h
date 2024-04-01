#pragma once
#include "Army.h"
#include "EarthGunnery.h"
#include "EarthSoldier.h"
#include "EarthTank.h"

class EarthArmy : public Army
{

	LinkedQueue<EarthSoldier> eSoldiersList;
	ArrayStack<EarthTank> eTanksList;
	priQueue<Unit*> eGunneryList;
public:
	void attack(Army* enemy) ;
	void addUnit(Unit*) ;
	void removeUnit(Unit*) ;

};

