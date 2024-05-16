#include "EarthArmy.h"
#include "Game.h"
#include <iomanip>

EarthArmy::EarthArmy(Game* pGame) : Army(pGame) {
	EarthUnit = nullptr;
	ES_Attack = nullptr;
	ET_Attack = nullptr;
	EG_Attack = nullptr;
	ES_attacking_list = nullptr;
	ET_attacking_list = nullptr;
	EG_attacking_list = nullptr;
	doneHealing = false;
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
		eGunneryList.enqueue(EarthUnit, EarthUnit->getPriority());  // pls check the priority function
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
			EarthUnit = nullptr;
		}

	}
	else if (type == "HU") {
		if (!healList.pop(EarthUnit)) {
			EarthUnit = nullptr;
		}
	}
	return EarthUnit;

}

bool EarthArmy::attack(Army* enemy, int timestep, bool& ES_total, bool& EG_total)
{
	Unit* EarthUnit;
	Unit* AlienUnit;
	/* Pointers for printing the fighting units*/
	bool F1= true, F2=true, F3=true;
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

		if (!EarthUnit->getInfectionStatus()) {
			/*First we will get the soldiers that will be attacked*/
			for (int i = 0;i < EarthUnit->getAttackCapacity();i++) {
				AlienUnit = enemy->removeUnit("AS");

				if (!AlienUnit) break;

				SoldierTemp.enqueue(AlienUnit);
				ES_attacking_list->enqueue(AlienUnit);
			}
			/* then we will start to attack them */
			EarthUnit->attack(&SoldierTemp, timestep, pGame, enemy);
		}
		else {
			Unit* Earth_attackedUnit;
			eSoldiersList.dequeue(EarthUnit);
			/*First we will get the soldiers that will be attacked*/
			for (int i = 0;i < EarthUnit->getAttackCapacity();i++) {
				Earth_attackedUnit = this->removeUnit("ES");

				if (!Earth_attackedUnit) break;

				SoldierTemp.enqueue(Earth_attackedUnit);
				ES_attacking_list->enqueue(Earth_attackedUnit);
			}
			/* then we will start to attack them */
			EarthUnit->attack(&SoldierTemp, timestep, pGame, enemy);
			eSoldiersList.enqueue(EarthUnit);
			while (SoldierTemp.dequeue(EarthUnit))
			{
				this->addUnit(EarthUnit);
			}
		}
	}
	else {
				F1 = false;
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

			EarthUnit->attack(&enemyTemp, timestep, pGame, enemy);

		}

		else {


			for (int i = 0; i < EarthUnit->getAttackCapacity(); i++) {
				AlienUnit = enemy->removeUnit("AM");

				if (!AlienUnit) break;

				enemyTemp.enqueue(AlienUnit);
				ET_attacking_list->enqueue(AlienUnit);
			}

			EarthUnit->attack(&enemyTemp, timestep, pGame, enemy);

		}
	}
	else {
		F2 = false;
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
		EarthUnit->attack(&enemytemp, timestep, pGame, enemy);
	}
	else {
		F3 = false;
	}

	if (eSoldiersList.getCount() == eSoldiersList.getCount() + eTanksList.getCount() + eGunneryList.getCount())
		ES_total = true;
	else 
		ES_total = false;

	if(eGunneryList.getCount() == eSoldiersList.getCount() + eTanksList.getCount() + eGunneryList.getCount())
		EG_total = true;
	else
		EG_total = false;




	return F1 || F2 || F3;
}

void EarthArmy::InfectionSpread() {
	if (rand() < 0.02) {
		LinkedQueue<Unit*> temp_ES_List;
		int randES = rand() % eSoldiersList.getCount();
		Unit* theinfected = nullptr;
		Unit* theinfectiuos = nullptr;
		int count = eSoldiersList.getCount();
		for (int i = 0; i < count; i++) {
			Unit* temp;
			eSoldiersList.dequeue(temp);
			temp_ES_List.enqueue(temp);
			if (i == randES) {
				theinfected = temp;
			}
			if (temp->getInfectionStatus()) {
			 theinfectiuos = temp;
			 if (i == randES && randES == eSoldiersList.getCount() - 1)
			 {
				  temp_ES_List.peek(theinfected);
			 }
			 else if (i == randES) {
				 randES = i+1 + rand() % (eSoldiersList.getCount()-i-1);//get another random number
			 }
			}
		}
		if (theinfected && theinfectiuos) {
			theinfected->setInfectionStatus(true);
		}
		for (int i = 0; i < count; i++) {
			Unit* temp;
			temp_ES_List.dequeue(temp);
			eSoldiersList.enqueue(temp);
		}
	}

}



int EarthArmy::getSoldiersCount()
{
	return eSoldiersList.getCount();
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
				if (temp->getInfectionStatus() == true) {
					Unit::decrementInfectedCount();
				}
				soldiersUML.enqueue(temp, INT_MAX - temp->getHealth());
				
				temp->setUMLJoinTime(timeStep);
			}

			else eSoldiersList.enqueue(temp);
		}


	}

	for (int i = 0; i < loop2; i++) {


		if (eTanksList.pop(temp)) {
			if (temp->getHealth() > 0 && temp->getHealth() < 0.2 * temp->getOriginalHealth()) {
				tankUML.enqueue(temp);
				temp->setUMLJoinTime(timeStep);
			}
			else
				tempStack.push(temp);
		}
		temp = nullptr;

		for (int i = 0; i < loop2; i++) {
			if (tempStack.pop(temp))
				eTanksList.push(temp);
		}
	}

}

void EarthArmy::Heal(int timeStep)
{
	Unit* healingUnit;

	HU_Healing = nullptr;
	HU_healing_list = new LinkedQueue<Unit*>;

	/*Here Earth healUnit Will heal Earth Soldiers and tanks Depend on its attack capacity*/
	if (!healList.isEmpty()) {

		healList.peek(healingUnit);
		HU_Healing = healingUnit; // for printing
		Unit* unitToHeal;
		double tempHealth;
		int healCapacity = healingUnit->getAttackCapacity();
		LinkedQueue<Unit*> needHealingList;

		if (healingUnit) {

			for (int i = 0; i < healCapacity; i++) {

				if (!soldiersUML.isEmpty()) {
					soldiersUML.dequeue(unitToHeal, tempHealth);
					needHealingList.enqueue(unitToHeal);
					HU_healing_list->enqueue(unitToHeal);
				}

				else if (!tankUML.isEmpty()) {
					tankUML.dequeue(unitToHeal);
					needHealingList.enqueue(unitToHeal);
					HU_healing_list->enqueue(unitToHeal);
				}

				else {
					break;
				}

			}

			healingUnit->attack(&needHealingList, timeStep, pGame, this);

			LinkedQueue<Unit*>* tempList = dynamic_cast<healUnit*>(healingUnit)->getTempList();
			
			for (int i = 0; i < tempList->getCount(); i++) {

				if (tempList->dequeue(unitToHeal)) {
					if (dynamic_cast<EarthSoldier*>(unitToHeal)) {
						soldiersUML.enqueue(unitToHeal, INT_MAX - unitToHeal->getHealth());
					}

					else if (dynamic_cast<EarthTank*>(unitToHeal)) {
						tankUML.enqueue(unitToHeal);
					}
				}

			}
		}

		healingUnit = nullptr;
	}
}


void EarthArmy::printArmy()
{
	std::cout << endl;
	std::cout << "\033[6;42m============================================ \033[0m" << endl;
	std::cout << "\033[6;42m==========\033[0m \033[1;32mEarth Army Alive Units\033[0m \033[6;42m========== \033[0m" << endl;
	std::cout << "\033[6;42m============================================ \033[0m" << endl;
	std::cout << endl;
	std::cout << "\033[1;32m";
	if (eSoldiersList.getCount() > 0)
		std::cout << eSoldiersList.getCount() << " ES " << " Infected % : " << std::setprecision(4) << calcinfectedperc() << " ";
	else
		std::cout << eSoldiersList.getCount() << " ES ";
	eSoldiersList.print();
	std::cout << eTanksList.getCount() << " ET ";
	eTanksList.print();
	std::cout << eGunneryList.getCount() << " EG ";
	eGunneryList.print();
	std::cout << healList.getCount() << " HU ";
	healList.print();
	std::cout << endl;
	std::cout << "\033[0m";
	std::cout << endl;
	std::cout << "\033[6;41m================================== \033[0m" << endl;
	std::cout << "\033[6;41m=====\033[0m \033[1;31mUnit Maintenance Lists\033[0m \033[6;41m===== \033[0m" << endl;
	std::cout << "\033[6;41m================================== \033[0m" << endl;
	std::cout << endl;
	std::cout << "\033[1;31m";
	std::cout << soldiersUML.getCount() << " ES ";
	soldiersUML.print();
	std::cout << tankUML.getCount() << " ET ";
	tankUML.print();
	std::cout << endl;
	std::cout << "\033[0m";



}

void EarthArmy::printFightingUnits()
{
	if (ES_Attack && ES_attacking_list && !ES_attacking_list->isEmpty()) {
		std::cout << "ES " << ES_Attack->getID() << " shoots ";
		ES_attacking_list->print();
	}

	if (ET_Attack && ET_attacking_list && !ET_attacking_list->isEmpty()) {
		std::cout << "ET " << ET_Attack->getID() << " shoots ";
		ET_attacking_list->print();
	}

	if (EG_Attack &&  EG_attacking_list && !EG_attacking_list->isEmpty()) {
		std::cout << "EG " << EG_Attack->getID() << " shoots ";
		EG_attacking_list->print();
	}

	if (HU_Healing && HU_healing_list && !HU_healing_list->isEmpty()) {
		std::cout << "\033[6;31m";
		std::cout << "HU " << HU_Healing->getID() << " Healing ";
		HU_healing_list->print();
		std::cout << "\033[0m";
	}

	delete ES_attacking_list;
	delete ET_attacking_list;
	delete EG_attacking_list;
	delete HU_healing_list;
	ES_attacking_list = nullptr;
	ET_attacking_list = nullptr;
	EG_attacking_list = nullptr;
	HU_healing_list = nullptr;


}

void EarthArmy::Armyfile(fstream& Output, int Df, int Dd, int ES_dead, int ET_dead, int EG_dead, int HU_dead = 0)
{
	Output << std::fixed << std::setprecision(2);
	Output << eSoldiersList.getCount() << " ES " << "  " 
		   << eTanksList.getCount() << " ET " << "  " 
		   << eGunneryList.getCount() << " EG" << "  " 
		   << healList.getCount() << " HU" << endl;
	Output << endl;
	Output <<( ((eSoldiersList.getCount() + ES_dead))? (double(Unit::getTotalInfected()) / (eSoldiersList.getCount() + ES_dead )) * 100 : 0)<< " %(Infected_ES) "
		   <<( ((eSoldiersList.getCount() + ES_dead))? (double(ES_dead) / (eSoldiersList.getCount() + ES_dead)) * 100 : 0) << " %(Dead_ES) " << endl
		   <<( ((eTanksList.getCount() + ET_dead))? (double(ET_dead) / (eTanksList.getCount() + ET_dead)) * 100 : 0 ) << " %(Dead_ET) "
		   <<( ((eGunneryList.getCount() + EG_dead))? (double(EG_dead) / (eGunneryList.getCount() + EG_dead)) * 100 : 0) << " %(Dead_EG)" << endl
	       <<( ((healList.getCount() + HU_dead))? (double(HU_dead) / (healList.getCount() + HU_dead)) * 100 : 0) << " %(Dead_HU) " << endl;
	Output << endl;
	Output << (((eSoldiersList.getCount() + eTanksList.getCount() + eGunneryList.getCount() + ES_dead + ET_dead + EG_dead) != 0) ?
		  (double(ES_dead + ET_dead + EG_dead) / (eSoldiersList.getCount() + eTanksList.getCount() + eGunneryList.getCount() + ES_dead + ET_dead + EG_dead)) * 100 : 0) << " %(Dead_EarthUnits)" << endl;
	Output << endl;
	int sum = ES_dead + ET_dead + EG_dead;
	if (sum != 0) {
		double Df_avg = (double(Df) / (sum));
		double Dd_avg = (double(Dd) / (sum));
		double Db_avg = (double(Df + Dd) / (sum));
		Output << "average of Df = " << Df_avg << endl;
		Output << "average of Dd = " << Dd_avg << endl;
		Output << "average of Db = " << Db_avg << endl;
		Output << endl;
		if (Db_avg != 0) {
			Output << "Df/Db % = " << (double(Df_avg) / Db_avg) * 100 << endl;
			Output << "Dd/Db % = " << (double(Dd_avg) / Db_avg) * 100 << endl;
		}
		else {
			Output << "Df/Db % = 0" << endl;
			Output << "Dd/Db % = 0" << endl;
		}
	}
	else {
		Output << "average of Df = 0 %" << endl;
		Output << "average of Dd = 0 %" << endl;
		Output << "average of Db = 0 %" << endl;
		Output << endl;
		Output << "Df/Db % = 0" << endl;
		Output << "Dd/Db % = 0" << endl;
	}
}


double EarthArmy::calcinfectedperc()
{

	return double(Unit::getInfectedCount() * 100)/eSoldiersList.getCount() ;
}

void EarthArmy::witthdrawallUML()
{
	Unit* temp;
	double tem_p;
	while (soldiersUML.dequeue(temp,tem_p)) {
		pGame->AddToKilled(temp);
	}
	while (tankUML.dequeue(temp)) {
		pGame->AddToKilled(temp);
	}
}

EarthArmy::~EarthArmy()
{
	Unit* EarthUnit;
	double temp;
	while (eSoldiersList.dequeue(EarthUnit)) {
		delete EarthUnit;
		EarthUnit = nullptr;
	}
	while (eTanksList.pop(EarthUnit)) {
		delete EarthUnit;
		EarthUnit = nullptr;
	}
	while (eGunneryList.dequeue(EarthUnit,temp)) {
		delete EarthUnit;
		EarthUnit = nullptr;
	}
	while (healList.pop(EarthUnit)) {
		delete EarthUnit;
		EarthUnit = nullptr;
	}
}
