#include "AlienArmy.h"
#include "Game.h"
#include "iomanip"


AlienArmy::AlienArmy(Game* pGame) : Army(pGame)
{
	flag = 1; // so first remove for drones will remove the last one 
	AS_Attack = nullptr;
	AM_Attack = nullptr;
	AD_Attack = nullptr;
	AD2_Attack = nullptr;
	AS_attacking_list = nullptr;
	AM_attacking_list = nullptr;
	AD_attacking_list = nullptr;
	AD2_attacking_list = nullptr;
}

bool AlienArmy::attack(Army* enemy, int timestep)
{
	Unit* EarthUnit;
	Unit* AlienUnit;
	bool F1 =true, F2 = true, F3 = true;
	/* Pointers for printing the fighting units*/
	AS_Attack = nullptr;
	AM_Attack = nullptr;
	AD_Attack = nullptr;
	AD2_Attack = nullptr;
	AS_attacking_list = new LinkedQueue<Unit*>;
	AM_attacking_list = new LinkedQueue<Unit*>;
	AD_attacking_list = new LinkedQueue<Unit*>;
	AD2_attacking_list = new LinkedQueue<Unit*>;
	/*Here Alien Soldier Will attack Earth Soldiers Depend on its attack capacity*/
	if (!aSoldiersList.isEmpty()) {
		aSoldiersList.peek(AlienUnit);
		LinkedQueue<Unit*> SoldierTemp;
		AS_Attack = AlienUnit;
		/*First we will get the soldiers that will be attacked*/
		for (int i = 0;i < AlienUnit->getAttackCapacity();i++) {
			EarthUnit = enemy->removeUnit("ES");
			if (EarthUnit == nullptr) break;
			SoldierTemp.enqueue(EarthUnit);
			AS_attacking_list->enqueue(EarthUnit);
		}
		AlienUnit->attack(&SoldierTemp, timestep, pGame, enemy);

	}
	else {
				F1 = false;
	}
	/*Here Alien Monster Will attack both tanks and Earth Soldiers Depend on its attack capacity*/

	if (!aMonstersList.isEmpty()) {

		aMonstersList.Remove(AlienUnit);
		AM_Attack = AlienUnit;
		LinkedQueue<Unit*> enemyTemp;

		int tankCapacity = AlienUnit->getAttackCapacity() / 2;
		int soldierCapacity = AlienUnit->getAttackCapacity() - tankCapacity;

		for (int i = 0; i < AlienUnit->getAttackCapacity(); i++) {

			if (enemyTemp.getCount() < tankCapacity) {
				EarthUnit = enemy->removeUnit("ET");

				if (EarthUnit == nullptr) {
					tankCapacity = 0;
					soldierCapacity = AlienUnit->getAttackCapacity() - i;
				}
				else {
					enemyTemp.enqueue(EarthUnit);
					AM_attacking_list->enqueue(EarthUnit);
				}
			}
			else {
				EarthUnit = enemy->removeUnit("ES");
				if (EarthUnit == nullptr) break;
				enemyTemp.enqueue(EarthUnit);
				AM_attacking_list->enqueue(EarthUnit);
			}
		}
		AlienUnit->attack(&enemyTemp, timestep, pGame, enemy);
		aMonstersList.AddElement(AlienUnit);

	}
	else {
		F2 = false;
	}

	if (!aDronesList.isEmpty()) {
		Unit* secAlienUnit;
		aDronesList.dequeue(AlienUnit);
		AD_Attack = AlienUnit;
		aDronesList.RearDequeue(secAlienUnit);
		AD2_Attack = secAlienUnit;
		LinkedQueue<Unit*> enemyTemp;

		if (AlienUnit != nullptr && secAlienUnit != nullptr) {
			int firtankattacked = AlienUnit->getAttackCapacity() / 2;
			int firgunneryattacked = AlienUnit->getAttackCapacity() - firtankattacked;
			int sectankattacked = secAlienUnit->getAttackCapacity() / 2;
			int secgunneryattacked = secAlienUnit->getAttackCapacity() - sectankattacked;

			/////////first Drone////////////

			for (int i = 0; i < AlienUnit->getAttackCapacity(); i++) {
				bool isTankEmpty = false;
				if (i < firtankattacked) {
					EarthUnit = enemy->removeUnit("ET");
					if (EarthUnit == nullptr) {
						firtankattacked = 0;
						firgunneryattacked = AlienUnit->getAttackCapacity() - i;
						isTankEmpty = true;
					}
					else {
						enemyTemp.enqueue(EarthUnit);
						AD_attacking_list->enqueue(EarthUnit);
					}

				}
				else {
					EarthUnit = enemy->removeUnit("EG");

					if (EarthUnit == nullptr) {
						if (!isTankEmpty) {
							firtankattacked = AlienUnit->getAttackCapacity() - i;
							firgunneryattacked = 0;
						}
						else {
							break;
						}
					}
					else {
						enemyTemp.enqueue(EarthUnit);
						AD_attacking_list->enqueue(EarthUnit);
					}
				}
			}

			AlienUnit->attack(&enemyTemp, timestep, pGame, enemy);

			///////////////Now second Drone//////////////////////

			for (int i = 0; i < secAlienUnit->getAttackCapacity(); i++) {
				bool isTankEmpty = false;
				if (i < sectankattacked) {
					EarthUnit = enemy->removeUnit("ET");
					if (EarthUnit == nullptr) {
						sectankattacked = 0;
						secgunneryattacked = secAlienUnit->getAttackCapacity() - i;
						isTankEmpty = true;
					}
					else {
						enemyTemp.enqueue(EarthUnit);
						AD2_attacking_list->enqueue(EarthUnit);
					}

				}
				else {
					EarthUnit = enemy->removeUnit("EG");

					if (EarthUnit == nullptr) {
						if (!isTankEmpty) {
							sectankattacked = AlienUnit->getAttackCapacity() - i;
							secgunneryattacked = 0;
						}
						else {
							break;
						}
					}
					else {
						enemyTemp.enqueue(EarthUnit);
						AD2_attacking_list->enqueue(EarthUnit);
					}
				}
			}
			secAlienUnit->attack(&enemyTemp, timestep, pGame, enemy);

		}
		if (AlienUnit)
			aDronesList.enqueue(AlienUnit);
		if (secAlienUnit)
			aDronesList.enqueue(secAlienUnit);
	}
	else {
		F3 = false;
	}
	return F1 || F2 || F3;
}

void AlienArmy::addUnit(Unit* AlienUnit)
{
	if (dynamic_cast<AlienSoldier*>(AlienUnit)) {
		aSoldiersList.enqueue(AlienUnit);
	}
	else if (dynamic_cast<AlienMonster*>(AlienUnit)) {
		aMonstersList.AddElement(AlienUnit);
	}
	else if (dynamic_cast<AlienDrone*>(AlienUnit)) {
		aDronesList.enqueue(AlienUnit);
	}
}

Unit* AlienArmy::removeUnit(string type)
{
	if (type == "AS") {
		if (!aSoldiersList.dequeue(AlienUnit)) {
			AlienUnit = nullptr;
		}
	}
	else if (type == "AM") {

		if (aMonstersList.getCount() != 0) {
			if (!aMonstersList.Remove(AlienUnit)) {
				AlienUnit = nullptr;
			}
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
int AlienArmy::getSoldiersCount()
{
	return aSoldiersList.getCount();
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

void AlienArmy::printFightingUnits()
{
	if (AS_Attack && AS_attacking_list && !AS_attacking_list->isEmpty()) {
		std::cout << "AS " << AS_Attack->getID() << " Shots ";
		AS_attacking_list->print();
	}

	if (AM_Attack && AM_attacking_list && !AM_attacking_list->isEmpty()) {
		std::cout << "AM " << AM_Attack->getID() << " Shots ";
		AM_attacking_list->print();
	}

	if (AD_Attack && AD_attacking_list && !AD_attacking_list->isEmpty()) {
		std::cout << "AD " << AD_Attack->getID() << " Shots ";
		AD_attacking_list->print();
	}
	if (AD2_Attack && AD2_attacking_list && !AD2_attacking_list->isEmpty()) {
		std::cout << "AD " << AD2_Attack->getID() << " Shots ";
		AD2_attacking_list->print();
	}

	delete AS_attacking_list;
	delete AM_attacking_list;
	delete AD_attacking_list;
	delete AD2_attacking_list;
	AS_attacking_list = nullptr;
	AM_attacking_list = nullptr;
	AD_attacking_list = nullptr;
	AD2_attacking_list = nullptr;


}

void AlienArmy::Armyfile(fstream& Output, int Df, int Dd, int AS_dead, int AM_dead, int AD_dead, int X_dead)
{
	Output << std::fixed << std::setprecision(2);
	Output << aSoldiersList.getCount() << " AS " << "  " << aMonstersList.getCount() << " AM " << "  " << aDronesList.getCount() << " AD" << endl;
	Output << endl;
	Output <<( ((aSoldiersList.getCount() + AS_dead)!=0)? (double(AS_dead) / (aSoldiersList.getCount() + AS_dead)) * 100 : 0)<< " %(Dead_AS) "
		   <<( ((aMonstersList.getCount() + AM_dead)!=0)? (double(AM_dead) / (aMonstersList.getCount() + AM_dead)) * 100 : 0)<< " %(Dead_AM) "
	       <<( ((aDronesList.getCount() + AD_dead)!=0)? (double(AD_dead) / (aDronesList.getCount() + AD_dead)) * 100 : 0 )<< " %(Dead_AD)" << endl;


	Output << endl;
	Output << (((aSoldiersList.getCount() + aMonstersList.getCount() + aDronesList.getCount() + AS_dead + AM_dead + AD_dead) != 0)?
		(double(AS_dead + AM_dead + AD_dead) / (aSoldiersList.getCount() + aMonstersList.getCount() + aDronesList.getCount() + AS_dead + AM_dead + AD_dead)) * 100 : 0 ) << " %(Dead_AlienUnits)" << endl;
	Output << endl;
	int sum = AS_dead + AM_dead + AD_dead;
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

