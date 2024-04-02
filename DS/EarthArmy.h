#pragma once
#include "Army.h"
#include "EarthGunnery.h"
#include "EarthSoldier.h"
#include "EarthTank.h"

class EarthArmy : public Army
{

	LinkedQueue<Unit*> eSoldiersList;
	ArrayStack<Unit*> eTanksList;
	priQueue<Unit*> eGunneryList;
public:
	EarthArmy(Game* pgame);
	void attack(Army* enemy) ;
	void addUnit(Unit*) ;
	Unit* removeUnit(string type) ;

};

