#include "AlienSoldier.h"
#include "Game.h"
#include "LinkedQueue.h"

AlienSoldier::AlienSoldier(int id, int jointime, double health, double power, int attackcapacity) :Unit(id, "AS", jointime, health, power, attackcapacity)
{
}
void AlienSoldier::attack(LinkedQueue <Unit *>* SoldierTemp, int timestep , Game * pGame , Army *enemy)
{
	Unit* EarthUnit;

	/* then we will start to attack them */
	int loopCount = SoldierTemp->getCount();
	for (int i = 0;i < loopCount;i++) {
		SoldierTemp->dequeue(EarthUnit);

		if (!EarthUnit) break;

		EarthUnit->setfatime(timestep);
		double Damage = (Power + Health / 100) / (pow(EarthUnit->getHealth(), 0.5));
		EarthUnit->setHealth(EarthUnit->getHealth() - Damage);
		if (EarthUnit->getHealth() <= 0)  // after attack i have to check is the soldier dead or not 
		{
			if(EarthUnit->getInfectionStatus())
			   Unit::decrementInfectedCount();
			pGame->AddToKilled(EarthUnit);
		}
		else {
			enemy->addUnit(EarthUnit);
		}
	}








}
