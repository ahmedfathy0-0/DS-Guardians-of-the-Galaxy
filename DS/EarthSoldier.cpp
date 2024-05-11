#include "EarthSoldier.h"
#include "Game.h"
#include "LinkedQueue.h"

EarthSoldier::EarthSoldier(int id, int jointime, double health, double power, int attackcapacity) :Unit(id, "ES", jointime, health, power, attackcapacity)
{
}
void EarthSoldier::attack(LinkedQueue <Unit*>* SoldierTemp, int timestep, Game* pGame, Army* enemy)
{
	
	Unit* AttackedUnit;
	LinkedQueue<Unit*> EarthTemp; //used for if it attacks EarthSoldiers
	int loopCount = SoldierTemp->getCount();

	for (int i = 0; i < loopCount; i++) {
		SoldierTemp->dequeue(AttackedUnit);
		if (!AttackedUnit) break;
		AttackedUnit->setfatime(timestep);

		double Damage = (Power + Health / 100) / (pow(AttackedUnit->getHealth(), 0.5));
		AttackedUnit->setHealth(AttackedUnit->getHealth() - Damage);

		if (AttackedUnit->getHealth() <= 0)  // after attack i have to check is the soldier dead or not 
		{
			if (AttackedUnit->getType()=="ES" && AttackedUnit->getInfectionStatus()) {
				Unit::decrementInfectedCount();
			}
			pGame->AddToKilled(AttackedUnit);
		}
		else {
			if (AttackedUnit->getType() == "ES") {
				EarthTemp.enqueue(AttackedUnit);
			}
			else {
				enemy->addUnit(AttackedUnit);
			}
		}
	}
	while (EarthTemp.dequeue(AttackedUnit)) {
		SoldierTemp->enqueue(AttackedUnit);
	}


}

