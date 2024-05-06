#include "AlienDrone.h"
#include "Game.h"
#include "LinkedQueue.h"

AlienDrone::AlienDrone(int id, int jointime, double health, double power, int attackcapacity) :Unit(id, "AD", jointime, health, power, attackcapacity)
{
}
void AlienDrone::attack(LinkedQueue <Unit*>* SoldierTemp, int timestep, Game* pGame, Army* enemy)
{

	Unit* EarthUnit;
	
	int loopCount1 = SoldierTemp->getCount();
	for (int i = 0; i < loopCount1; i++) {
		SoldierTemp->dequeue(EarthUnit);

		if (!EarthUnit) break;
		double Damage = (Power + Health / 100) / (pow(EarthUnit->getHealth(), 0.5));
		EarthUnit->setHealth(EarthUnit->getHealth() - Damage);
		EarthUnit->setfatime(timestep);
		if (EarthUnit->getHealth() <= 0)  // after attack i have to check is the Monster dead or not 
		{
			pGame->AddToKilled(EarthUnit);
		}
		else {
			enemy->addUnit(EarthUnit);
		}
	}

}

