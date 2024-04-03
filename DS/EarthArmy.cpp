#include "EarthArmy.h"
#include "Game.h"

EarthArmy::EarthArmy(Game* pgame) : Army(pgame)
{
	EarthUnit = nullptr;
}

void EarthArmy::attack(Army* enemy)
{
	Unit* EarthUnit;
	Unit* AlienUnit;
	/*Here Earth Soldier Will attack Alien Soldiers Depend on its attack capacity*/
	if (!eSoldiersList.isEmpty()) {
		eSoldiersList.peek(EarthUnit);
		LinkedQueue<Unit*> SoldierTemp;
		/*First we will get the soldiers that will be attacked*/
		for (int i = 0;i < EarthUnit->getAttackCapacity();i++) {
			AlienUnit = enemy->removeUnit("AS");
			SoldierTemp.enqueue(AlienUnit);
		}
		/* then we will start to attack them */
		for (int i = 0;i < EarthUnit->getAttackCapacity();i++) {
			SoldierTemp.dequeue(AlienUnit);
			EarthUnit->attack(AlienUnit);
			if (AlienUnit->getHealth() <= 0)  // after attack i have to check is the soldier dead or not 
			{
				pGame->AddToKilled(AlienUnit);
			}
			else {
				SoldierTemp.enqueue(AlienUnit);  
			}
		}
		/*Now we need to return the alive soldiers to thier previous place again  */
		for (int i = 0;;i++) {
			AlienUnit = enemy->removeUnit("AS");
			SoldierTemp.enqueue(AlienUnit);
		}
		for (int i = 0; SoldierTemp.dequeue(AlienUnit);i++) {
			enemy->addUnit(AlienUnit);
		} // now every alive unit return thier places

	} 
}

void EarthArmy::addUnit(Unit* EarthUnit)
{
	if (EarthUnit->getType() == "ES") {
		eSoldiersList.enqueue(EarthUnit);
	}
	else if (EarthUnit->getType() == "ET") {
		eTanksList.push(EarthUnit);
	}
	else if (EarthUnit->getType() == "EG") {
		eGunneryList.enqueue(EarthUnit,EarthUnit->getPower());
	}
}

Unit* EarthArmy::removeUnit(string type)
{
	
	if (type == "ES") {
		eSoldiersList.dequeue(EarthUnit);
	}
	else if (type == "ET") {
		eTanksList.pop(EarthUnit);
	}
	else if (type == "EG") {
		double  pri;
		eGunneryList.dequeue(EarthUnit,pri);
	}
	return EarthUnit;

}
