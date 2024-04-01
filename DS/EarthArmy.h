#pragma once
#include "Army.h"
#include "EarthGunnery.h"
#include "EarthSoldier.h"
#include "EarthTank.h"

class EarthArmy : public Army
{

	LinkedQueue<EarthSoldier> eSoldiersList;
	ArrayStack<EarthTank> eTanksList;
	priQueue<EarthGunnery> eGunneryList;

};

