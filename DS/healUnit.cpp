#include "healUnit.h"
#include "Game.h"
#include "LinkedQueue.h"


healUnit::healUnit(int id, int jointime, double health, double power, int attackcapacity) :Unit(id, "HU", jointime, health, power, attackcapacity)
{
	doneHealing = false;
}

void healUnit::attack(LinkedQueue <Unit*>* needHealingList, int timeStep, Game* pGame, Army* earthArmy)
{
	Unit* unitToHeal;

	doneHealing = false;

	for (int i = 0; i < needHealingList->getCount(); i++) {
		needHealingList->dequeue(unitToHeal);

		if (timeStep - unitToHeal->getUMLJoinTime() > 10) {
			pGame->AddToKilled(unitToHeal);
		}

		else {
			heal(unitToHeal);
			doneHealing = true;

			if (unitToHeal->getHealth() > 0.2 * unitToHeal->getOriginalHealth()) { // if the unit is healed
				
				earthArmy->addUnit(unitToHeal);
				if (unitToHeal->getType() == "ES") {
					if (unitToHeal->getInfectionStatus()) {
						unitToHeal->setInfectionStatus(false);
						unitToHeal->setImmunityStatus(true);
					}
				}

			}

			else {
				tempList.enqueue(unitToHeal);
			}
		}
	}

	if (doneHealing) {
		this->fAtime = timeStep;
		pGame->AddToKilled(this);
	}
}

void healUnit::heal(Unit* unitToHeal)
{
	double healthImprovement = (Power * (Health/100)) / (pow(unitToHeal->getHealth(), 0.5));

	
	if (unitToHeal->getInfectionStatus() && (unitToHeal->getHealingCounter() < 2)) {

		healthImprovement = 0.5 * healthImprovement;

		unitToHeal->setHealingCounter(unitToHeal->getHealingCounter() + 1);

		if (unitToHeal->getHealingCounter() == 2)
			unitToHeal->setHealingCounter(0);
	}

	unitToHeal->setHealth(unitToHeal->getHealth() + healthImprovement);
}

LinkedQueue<Unit*>* healUnit::getTempList()
{
	return &tempList;
}

