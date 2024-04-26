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
				enemy->addUnit(AlienUnit);
			}
		}
	}

	/*Here Earth Tank Will attack Alien Monsters and maybe Soldiers Depend on its attack capacity*/

	if (!eTanksList.isEmpty()) {
		eTanksList.peek(EarthUnit);
		LinkedQueue<Unit*> enemyTemp;
		bool flag = false;
		int earthSoldiersCount = eSoldiersList.getCount();
		int alienSoldiersCount = enemy->getSoldiersCount();

		// To handle the condition of Tank attacking both Monsters and Soldiers

		if (flag && (earthSoldiersCount >= 0.8 * alienSoldiersCount)) {
			flag = false;
		}

		if (earthSoldiersCount < 0.3 * alienSoldiersCount || flag) {

			flag = true;

			int monstersCapacity = EarthUnit->getAttackCapacity() / 2;
			int soldiersCapacity = EarthUnit->getAttackCapacity() - monstersCapacity;

			for (int i = 0; i < EarthUnit->getAttackCapacity(); i++) {

				if (enemyTemp.getCount() < monstersCapacity) {
					AlienUnit = enemy->removeUnit("AM");
					enemyTemp.enqueue(AlienUnit);
				}
				else {
					AlienUnit = enemy->removeUnit("AS");
					enemyTemp.enqueue(AlienUnit);
				}
			}

			for (int i = 0; i < EarthUnit->getAttackCapacity(); i++) {

				enemyTemp.dequeue(AlienUnit);

				EarthUnit->attack(AlienUnit);

				if (AlienUnit->getHealth() <= 0)
				{
					pGame->AddToKilled(AlienUnit);
				}
				else {
					enemy->addUnit(AlienUnit);
				}

			}

		}

		else {

			for (int i = 0; i < EarthUnit->getAttackCapacity(); i++) {
				AlienUnit = enemy->removeUnit("AM");
				enemyTemp.enqueue(AlienUnit);
			}

			for (int i = 0; i < EarthUnit->getAttackCapacity(); i++) {
				enemyTemp.dequeue(AlienUnit);
				EarthUnit->attack(AlienUnit);
				if (AlienUnit->getHealth() <= 0)  // after attack i have to check is the Monster dead or not 
				{
					pGame->AddToKilled(AlienUnit);
				}
				else {
					enemy->addUnit(AlienUnit);
				}
			}
		}
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

int EarthArmy::getSoldiersCount()
{
	return eSoldiersList.getCount();
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
