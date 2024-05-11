#include "AlienMonster.h"
#include "Game.h"
#include "LinkedQueue.h"

AlienMonster::AlienMonster(int id, int jointime, double health, double power, int attackcapacity) :Unit(id, "AM", jointime, health, power, attackcapacity)
{
}


/// ############### NOTE ################
/// 
/// The AlienMonster attack function may not work properly if the input file is not yet modified @@@@@@@@@@ Tony and Fathy
/// 
/// ############### NOTE ################

void AlienMonster::attack(LinkedQueue <Unit*>* SoldierTemp, int timestep, Game* pGame, Army* enemy)
{
	Army* eartharmy = pGame->getEarthArmy();
	Unit* EarthUnit;
	int infectionProb = pGame->getInfectionProb();

	srand(time(0));

	int randNum = rand() % 100 + 1;
	
	int loopCount = SoldierTemp->getCount();
	for (int i = 0; i < loopCount; i++) {
		SoldierTemp->dequeue(EarthUnit);

		if (!EarthUnit) break;

		EarthUnit->setfatime(timestep);

		double Damage = (Power + Health / 100) / (pow(EarthUnit->getHealth(), 0.5));

		if (EarthUnit->getType() == "ES" && randNum <= infectionProb && !EarthUnit->getImmunityStatus()) {
			if (!EarthUnit->getInfectionStatus()) {
				EarthUnit->setInfectionStatus(true);
				Unit::incrementInfectedCount();
			}
				enemy->addUnit(EarthUnit);
			
		}

		else {
			EarthUnit->setHealth(EarthUnit->getHealth() - Damage);

			if (EarthUnit->getHealth() <= 0)
			{
				if(EarthUnit->getType() == "ES" && EarthUnit->getInfectionStatus())
					Unit::decrementInfectedCount();
				pGame->AddToKilled(EarthUnit);
			}
			else {
				enemy->addUnit(EarthUnit);
			}
		}
		
	}

}
