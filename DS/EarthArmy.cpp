#include "EarthArmy.h"

void EarthArmy::addUnit(Unit* EarthUnit)
{
	if (EarthUnit->getType() == "ES") {

	}
	else if (EarthUnit->getType() == "ET") {

	}
	else if (EarthUnit->getType() == "EG") {
		eGunneryList.enqueue(EarthUnit,EarthUnit->getPower());
	}
}
