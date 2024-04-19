#include "EarthArmy.h"
#include "Game.h"

EarthArmy::EarthArmy(Game* pGame): Army(pGame) {
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
	if (dynamic_cast<EarthSoldier*>(EarthUnit)) {
		eSoldiersList.enqueue(EarthUnit);
	}
	else if (dynamic_cast<EarthTank*>(EarthUnit)) {
		eTanksList.push(EarthUnit);
	}
	else if (dynamic_cast<EarthGunnery*>(EarthUnit)) {
		eGunneryList.enqueue(EarthUnit,EarthUnit->getPriority());  // pls check the priority function
	}
}

Unit* EarthArmy::removeUnit(string type)
{
	
	if (type == "ES") {
		if (!eSoldiersList.dequeue(EarthUnit)) {
			EarthUnit = nullptr;
		}
	}
	else if (type == "ET") {
		if (!eTanksList.pop(EarthUnit)) {
			EarthUnit = nullptr;
		}
		
	}
	else if (type == "EG") {
		double  pri;
		if (!eGunneryList.dequeue(EarthUnit, pri)) {
			EarthUnit= nullptr;
		}

	}
	return EarthUnit;

}

void EarthArmy::printArmy()
{
	std::cout << "====================== Earth Army Alive Units ====================== " << endl;
	std::cout << eSoldiersList.getCount() << " ES ";
	eSoldiersList.print();
	std::cout << eTanksList.getCount() << " ET ";
	eTanksList.print();
	std::cout << eGunneryList.getCount() << " EG ";
	eGunneryList.print();

	std::cout << endl;


}
