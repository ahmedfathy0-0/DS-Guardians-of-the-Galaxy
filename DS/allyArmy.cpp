#include "allyArmy.h"
#include "saverUnit.h"

allyArmy::allyArmy(Game* pGame): Army(pGame)
{
	allyUnit = nullptr;
}

void allyArmy::attack(Army* enemy, int timestep)
{
}

void allyArmy::addUnit(Unit* allyUnit)
{
	if (dynamic_cast<saverUnit*>(allyUnit)) {
		saverUnitsList.enqueue(allyUnit);
	}
}

Unit* allyArmy::removeUnit(string type)
{
	if (type == "SU") {
		if (!saverUnitsList.dequeue(allyUnit)) {
			allyUnit = nullptr;
		}
	}

	return allyUnit;
}

int allyArmy::getSoldiersCount()
{
	return saverUnitsList.getCount();
}

void allyArmy::printArmy()
{
	std::cout << "====================== Ally Army Alive Units ====================== " << endl;
	std::cout << saverUnitsList.getCount() << " SU ";
	saverUnitsList.print();
	std::cout << endl;
}

void allyArmy::printFightingUnits()
{

}

void allyArmy::Armyfile(fstream&, int, int, int, int, int)
{
}
