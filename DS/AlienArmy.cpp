#include "AlienArmy.h"
#include "Game.h"


AlienArmy::AlienArmy()
{
	flag = 1; // so first remove for drones will remove the last one 
}

void AlienArmy::attack(Army* enemy, Game* pGame)
{
	Unit* EarthUnit;
	Unit* AlienUnit;
	/*Here Alien Soldier Will attack Earth Soldiers Depend on its attack capacity*/
	if (!aSoldiersList.isEmpty()) {
		aSoldiersList.peek(AlienUnit);
		LinkedQueue<Unit*> SoldierTemp;
		/*First we will get the soldiers that will be attacked*/
		for (int i = 0;i < AlienUnit->getAttackCapacity();i++) {
			EarthUnit = enemy->removeUnit("ES");
			SoldierTemp.enqueue(EarthUnit);
		}
		/* then we will start to attack them */
		for (int i = 0;i < AlienUnit->getAttackCapacity();i++) {
			SoldierTemp.dequeue(EarthUnit);
			AlienUnit->attack(EarthUnit);
			if (EarthUnit->getHealth() <= 0)  // after attack i have to check is the soldier dead or not 
			{
				pGame->AddToKilled(EarthUnit);
			}
			else {
				SoldierTemp.enqueue(EarthUnit);
			}
		}
		/*Now we need to return the alive soldiers to thier previous place again  */
		for (int i = 0;;i++) {
			EarthUnit = enemy->removeUnit("AS");
			SoldierTemp.enqueue(EarthUnit);
		}
		for (int i = 0; SoldierTemp.dequeue(EarthUnit);i++) {
			enemy->addUnit(EarthUnit);
		} // now every alive unit return thier places

	}
}

void AlienArmy::addUnit(Unit* AlienUnit)
{
	if (AlienUnit->getType() == "AS") {
		aSoldiersList.enqueue(AlienUnit);
	}
	else if (AlienUnit->getType() == "AM") {
		aMonstersList.AddElement(AlienUnit);
	}
	else if (AlienUnit->getType() == "AD") {
		aDronesList.enqueue(AlienUnit);
	}
}

Unit* AlienArmy::removeUnit(string type)
{
	int index=0;
	if (type == "AS") {
		aSoldiersList.dequeue(AlienUnit);
	}
	else if (type == "AM") {

		if (aMonstersList.getCount() != 0) {
			index = rand() % (aMonstersList.getCount()); //get random monster
			aMonstersList.Remove(index, AlienUnit);
		}

		else return nullptr;
		
	}

	else if (type == "AD") {

		bool res;

		if (flag) {
			res = aDronesList.dequeue(AlienUnit);
		}
		else {
			res = aDronesList.RearDequeue(AlienUnit);
		}

		if (!res) {
			AlienUnit = nullptr;
		}
		else {
			flag = !flag;
		}
	}
	return AlienUnit;
}
void AlienArmy::printArmy()
{
	std::cout << "====================== Alien Army Alive Units ====================== " << endl;
	std::cout << aSoldiersList.getCount() << " AS ";
	aSoldiersList.print();
	std::cout << aMonstersList.getCount() << " AM ";
	aMonstersList.print();
	std::cout << aDronesList.getCount() << " AD ";
	aDronesList.print();

	std::cout << endl;


}
		
