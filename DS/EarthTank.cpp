#include "EarthTank.h"
#include "Game.h"
#include "LinkedQueue.h"


EarthTank::EarthTank(int id, int jointime, double health, double power, int attackcapacity) :Unit(id, "ET", jointime, health, power, attackcapacity)
{
	originalHealth = health;
}
void EarthTank::attack(LinkedQueue <Unit*>* SoldierTemp, int timestep, Game* pGame, Army* enemy)
{
	
	Unit * AlienUnit;
	int loopCount = SoldierTemp->getCount();
	for (int i = 0; i < loopCount; i++) {
		SoldierTemp->dequeue(AlienUnit);

		if (!AlienUnit) break;

		AlienUnit->setfatime(timestep);
		double Damage = (Power + Health / 100) / (pow(AlienUnit->getHealth(), 0.5));
		AlienUnit->setHealth(AlienUnit->getHealth() - Damage);

		if (AlienUnit->getHealth() <= 0)
		{
			pGame->AddToKilled(AlienUnit);
		}
		else {
			enemy->addUnit(AlienUnit);
		}

	}



}
