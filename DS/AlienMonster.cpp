#include "AlienMonster.h"
#include "Game.h"
#include "LinkedQueue.h"

AlienMonster::AlienMonster(int id, int jointime, double health, double power, int attackcapacity) :Unit(id, "AM", jointime, health, power, attackcapacity)
{
}
void AlienMonster::attack(LinkedQueue <Unit*>* SoldierTemp, int timestep, Game* pGame, Army* enemy)
{
	Unit* EarthUnit;

	int loopCount = SoldierTemp->getCount();
	for (int i = 0; i < loopCount; i++) {
		SoldierTemp->dequeue(EarthUnit);

		if (!EarthUnit) break;

		EarthUnit->setfatime(timestep);

		double Damage = (Power + Health / 100) / (pow(EarthUnit->getHealth(), 0.5));
		EarthUnit->setHealth(EarthUnit->getHealth() - Damage);
		if (EarthUnit->getHealth() <= 0)
		{
			pGame->AddToKilled(EarthUnit);
		}
		else {
			enemy->addUnit(EarthUnit);
		}
	}






}
