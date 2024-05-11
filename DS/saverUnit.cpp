#include "saverUnit.h"
#include "Game.h"
#include "LinkedQueue.h"

saverUnit::saverUnit(int id, int jointime, double health, double power, int attackcapacity) :Unit(id, "SU", jointime, health, power, attackcapacity)
{
}

void saverUnit::attack(LinkedQueue<Unit*>* enemyTemp, int timestep, Game* pGame, Army* enemy)
{
	Unit* AttackedUnit;
	int loopCount = enemyTemp->getCount();

	for (int i = 0; i < loopCount; i++) {
		enemyTemp->dequeue(AttackedUnit);
		if (!AttackedUnit) break;
		AttackedUnit->setfatime(timestep);

		double Damage = (Power + Health / 100) / (pow(AttackedUnit->getHealth(), 0.5));
		AttackedUnit->setHealth(AttackedUnit->getHealth() - Damage);

		if (AttackedUnit->getHealth() <= 0)  // after attack i have to check is the soldier dead or not 
		{
			pGame->AddToKilled(AttackedUnit);
		}
		else {
		    enemy->addUnit(AttackedUnit);
		}
	}


}
