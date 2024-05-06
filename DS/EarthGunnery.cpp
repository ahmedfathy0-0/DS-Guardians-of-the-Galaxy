#include "EarthGunnery.h"
#include "Game.h"
#include "LinkedQueue.h"

EarthGunnery::EarthGunnery(int id, int jointime, double health, double power, int attackcapacity) :Unit(id, "EG", jointime, health, power, attackcapacity)
{

}



void EarthGunnery::attack(LinkedQueue <Unit*>* SoldierTemp, int timestep, Game* pGame, Army* enemy)
{
	
	Unit* AlienUnit;

	int loopCount = SoldierTemp->getCount();
	for (int i = 0; i < loopCount; i++) {
		SoldierTemp->dequeue(AlienUnit);

		if (!AlienUnit) break;

		AlienUnit->setfatime(timestep);

		double Damage = (Power + Health / 100) / (pow(AlienUnit->getHealth(), 0.5));
		AlienUnit->setHealth(AlienUnit->getHealth() - Damage);
		if (AlienUnit->getHealth() <= 0)  // after attack i have to check is the Monster dead or not 
		{
			pGame->AddToKilled(AlienUnit);
		}
		else {
			enemy->addUnit(AlienUnit);
		}
	}




}
