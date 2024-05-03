#include "EarthArmy.h"
#include "Game.h"
#include <iomanip>

EarthArmy::EarthArmy(Game* pGame): Army(pGame) {
	EarthUnit = nullptr;
}

void EarthArmy::attack(Army* enemy , int timestep)
{
	Unit* EarthUnit;
	Unit* AlienUnit;
	/* Pointers for printing the fighting units*/
	ES_Attack = nullptr;
	ET_Attack = nullptr;
	EG_Attack = nullptr;
	ES_attacking_list = new LinkedQueue<Unit*>;
	ET_attacking_list = new LinkedQueue<Unit*>;
	EG_attacking_list = new LinkedQueue<Unit*>;

	/*Here Earth Soldier Will attack Alien Soldiers Depend on its attack capacity*/
	if (!eSoldiersList.isEmpty()) {
		eSoldiersList.peek(EarthUnit);

		ES_Attack = EarthUnit; // for printing

		LinkedQueue<Unit*> SoldierTemp;
		/*First we will get the soldiers that will be attacked*/
		for (int i = 0;i < EarthUnit->getAttackCapacity();i++) {
			AlienUnit = enemy->removeUnit("AS");

			if (!AlienUnit) break;

			SoldierTemp.enqueue(AlienUnit);
			ES_attacking_list->enqueue(AlienUnit);
		}
		/* then we will start to attack them */

		int loopCount = SoldierTemp.getCount();

		for (int i = 0; i < loopCount; i++) {
			SoldierTemp.dequeue(AlienUnit);

			if (!AlienUnit) break;

			AlienUnit->setfatime(timestep);

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

		ET_Attack = EarthUnit; // for printing

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

					if (!AlienUnit) {
						monstersCapacity = enemyTemp.getCount();
						soldiersCapacity = EarthUnit->getAttackCapacity() - monstersCapacity;
						continue;
					}
					
					enemyTemp.enqueue(AlienUnit);
					ET_attacking_list->enqueue(AlienUnit);
				}
				else {
					AlienUnit = enemy->removeUnit("AS");

					if (!AlienUnit) break;

					enemyTemp.enqueue(AlienUnit);
					ET_attacking_list->enqueue(AlienUnit);
				}
			}
            int loopCount=enemyTemp.getCount();

			for (int i = 0; i < loopCount; i++) {
				enemyTemp.dequeue(AlienUnit);

				if (!AlienUnit) break;

				AlienUnit->setfatime(timestep);
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

				if (!AlienUnit) break;

				enemyTemp.enqueue(AlienUnit);
				ET_attacking_list->enqueue(AlienUnit);
			}

			int loopCount = enemyTemp.getCount();

			for (int i = 0; i < loopCount; i++) {

				enemyTemp.dequeue(AlienUnit);

				if (!AlienUnit) break;

				AlienUnit->setfatime(timestep);

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


	/*Here Earth gunnery Will attack Alien monsters and drones Depend on its attack capacity*/
	if (!eGunneryList.isEmpty()) {
		double pri = 0.0;
		eGunneryList.peek(EarthUnit, pri);

		EG_Attack = EarthUnit; // for printing

		LinkedQueue<Unit*> enemytemp;
		
		int attackCapacity = EarthUnit->getAttackCapacity();
		int monstersAttacked = EarthUnit->getAttackCapacity() / 2;
		int dronesAttacked = EarthUnit->getAttackCapacity() - monstersAttacked;

		bool isMonsterEmpty = false;
		for (int i = 0; i < EarthUnit->getAttackCapacity(); i++) {
			
			if (i < monstersAttacked) {
				AlienUnit = enemy->removeUnit("AM");
				if (AlienUnit == nullptr) {
					monstersAttacked = 0;
					dronesAttacked = EarthUnit->getAttackCapacity() - i;
					isMonsterEmpty = true;
				}
				else {
					enemytemp.enqueue(AlienUnit);
					EG_attacking_list->enqueue(AlienUnit);
				}

			}
			else {
				AlienUnit = enemy->removeUnit("AD");

				if (AlienUnit == nullptr) {
					if (!isMonsterEmpty) {
						monstersAttacked = EarthUnit->getAttackCapacity() - i;
						dronesAttacked = 0;
					}
					else {
						break;
					}
				}
				else {
					enemytemp.enqueue(AlienUnit);
					EG_attacking_list->enqueue(AlienUnit);
				}
			}
		}
         int loopCount = enemytemp.getCount();
		for (int i = 0; i < loopCount; i++) {
			enemytemp.dequeue(AlienUnit);

			if (!AlienUnit) break;

			AlienUnit->setfatime(timestep);

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
	else if (dynamic_cast<healUnit*>(EarthUnit)) {
		healList.push(EarthUnit);
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
	else if (type == "HU") {
		if (!healList.pop(EarthUnit)) {
			EarthUnit = nullptr;
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
	std::cout << healList.getCount() << " HU ";
	healList.print();
	std::cout << endl;
	std::cout << "======================  Unit Maintenance Lists ====================== " << endl;
	std::cout << soldiersUML.getCount() << " ES ";
	soldiersUML.print();
	std::cout << tankUML.getCount() << " ET ";
	tankUML.print();
	std::cout << endl;
    


}

void EarthArmy::modifyUML(int timeStep)
{
	Unit* temp;
	ArrayStack<Unit*> tempStack;
	int loop1 = eSoldiersList.getCount();
	int loop2 = eTanksList.getCount();

	for (int i = 0; i < loop1; i++) {
		eSoldiersList.dequeue(temp);

		if (temp) {
			if (temp->getHealth() > 0 && temp->getHealth() < 0.2 * temp->getOriginalHealth()) {
				soldiersUML.enqueue(temp, temp->getHealth());
				temp->setUMLJoinTime(timeStep);
			}

			else eSoldiersList.enqueue(temp);
		}

		
	}

	for (int i = 0; i < loop2; i++) {
		eTanksList.pop(temp);
		tempStack.push(temp);

		if (temp) {
			if (temp->getHealth() > 0 && temp->getHealth() < 0.2 * temp->getOriginalHealth()) {
				tankUML.enqueue(temp);
				temp->setUMLJoinTime(timeStep);
			}
		}
	}

	for (int i = 0; i < loop2; i++) {
		tempStack.pop(temp);
		eTanksList.push(temp);
	}

}

void EarthArmy::Heal(int timeStep)
{
	Unit* EarthUnit;

	/*Here Earth healUnit Will heal Earth Soldiers and tanks Depend on its attack capacity*/
	if (!healList.isEmpty()) {
		healList.pop(EarthUnit);
		LinkedQueue<Unit*> tempList;
		Unit* unitToHeal;
		double tempHealth;
		int healCapacity = EarthUnit->getAttackCapacity();

		if (EarthUnit) {
			for (int i = 0; i < healCapacity; i++) {

				if (!soldiersUML.isEmpty()) {
					soldiersUML.dequeue(unitToHeal, tempHealth);
				}

				else if (!tankUML.isEmpty()) {
					tankUML.dequeue(unitToHeal);
				}

				else {
					break;
				}

				if (timeStep - unitToHeal->getUMLJoinTime() > 10) {
					pGame->AddToKilled(unitToHeal);
				}

				else {
					EarthUnit->attack(unitToHeal);

					if (unitToHeal->getHealth() > 0.2 * unitToHeal->getOriginalHealth()) {
						this->addUnit(unitToHeal);
					}

					else {
						tempList.enqueue(unitToHeal);
					}

				}

			}

			for (int i = 0; i < tempList.getCount(); i++) {

				if (tempList.dequeue(unitToHeal)) {
					if (dynamic_cast<EarthSoldier*>(unitToHeal)) {
						soldiersUML.enqueue(unitToHeal, unitToHeal->getHealth());
					}

					else if (dynamic_cast<EarthTank*>(unitToHeal)) {
						tankUML.enqueue(unitToHeal);
					}
				}
			
			}

			pGame->AddToKilled(EarthUnit);

		}

	}
}

void EarthArmy::printFightingUnits()
{
	if (ES_Attack && !ES_attacking_list->isEmpty()) {
		std::cout << "ES " << ES_Attack->getID() << " Shots ";
		ES_attacking_list->print();
	}

	if (ET_Attack && !ET_attacking_list->isEmpty()) {
		std::cout << "ET " << ET_Attack->getID() << " Shots ";
		ET_attacking_list->print();
	}
	
	if (EG_Attack && !EG_attacking_list->isEmpty()) {
		std::cout << "EG " << EG_Attack->getID() << " Shots ";
		EG_attacking_list->print();
	}

	delete ES_attacking_list;
	delete ET_attacking_list;
	delete EG_attacking_list;
	ES_attacking_list = nullptr;
	ET_attacking_list = nullptr;
	EG_attacking_list = nullptr;


}

void EarthArmy::Armyfile(fstream& Output, int ES_dead, int ET_dead, int EG_dead, int Df, int Dd)
{
	Output << std::fixed << std::setprecision(2);
	Output << eSoldiersList.getCount() << " ES " << "  " << eTanksList.getCount() << " ET " << "  " << eGunneryList.getCount() << " EG" << endl;
	Output << endl;
	Output << ( double(ES_dead) / (eSoldiersList.getCount() + ES_dead)) * 100 << " %(Dead_ES) " << (double(ET_dead) / (eTanksList.getCount() + ET_dead)) * 100 << " %(Dead_ET) " << (double(EG_dead) / (eGunneryList.getCount() + EG_dead)) * 100 << " %(Dead_EG)" << endl;
	Output << endl;
	Output << (double(ES_dead + ET_dead + EG_dead) / (eSoldiersList.getCount() + eTanksList.getCount() + eGunneryList.getCount() + ES_dead + ET_dead + EG_dead)) * 100 << " %(Dead_EarthUnits)" << endl;
	Output << endl;
	int Df_avg = (double(Df) / (ES_dead + ET_dead + EG_dead));
	int Dd_avg = (double(Dd) / (ES_dead + ET_dead + EG_dead));
	int Db_avg = (double(Df + Dd) / (ES_dead + ET_dead + EG_dead));
	Output << "average of Df = " << Df_avg << endl;
	Output << "average of Dd = " << Dd_avg << endl;
	Output << "average of Db = " << Db_avg << endl;
	Output << endl;	
	Output << "Df/Db % = " << (double(Df_avg) / Db_avg) * 100 << endl;
	Output << "Dd/Db % = " << (double(Dd_avg) / Db_avg) * 100 << endl;
}
