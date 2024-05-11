#include "allyArmy.h"
#include "saverUnit.h"
#include "iomanip"
#include "fstream"


allyArmy::allyArmy(Game* pGame): Army(pGame)
{
	allyUnit = nullptr;
}

bool allyArmy::attack(Army* enemy, int timestep)
{
	Unit* AllyUnit;
	Unit* AlienUnit;
	/* Pointers for printing the fighting units*/
	SU_attack = nullptr;
	SU_attacking_list = new LinkedQueue<Unit*>;

	/*Here Earth Soldier Will attack Alien Soldiers Depend on its attack capacity*/
	if (!saverUnitsList.isEmpty()) {
		saverUnitsList.peek(AllyUnit);

		SU_attack = AllyUnit; // for printing

		LinkedQueue<Unit*> SoldierTemp;
		/*First we will get the soldiers that will be attacked*/
		for (int i = 0;i < AllyUnit->getAttackCapacity();i++) {
			AlienUnit = enemy->removeUnit("AS");

			if (!AlienUnit) break;

			SoldierTemp.enqueue(AlienUnit);
			SU_attacking_list->enqueue(AlienUnit);
		}
		/* then we will start to attack them */
		AllyUnit->attack(&SoldierTemp, timestep, pGame, enemy);
	}
	else
		return false;


}

void allyArmy::Withdrawal()
{
	Unit* su;
	while (saverUnitsList.dequeue(su)) {
		delete su;
		su = NULL;
	}
}

void allyArmy::addUnit(Unit* allyUnit)
{
	if (dynamic_cast<saverUnit*>(allyUnit)) {
		saverUnitsList.enqueue(allyUnit);
	}
}

Unit* allyArmy::removeUnit(string type)
{
	if (type == "SU") {
		if (!saverUnitsList.dequeue(allyUnit)) {
			allyUnit = nullptr;
		}
	}

	return allyUnit;
}

int allyArmy::getSoldiersCount()
{
	return saverUnitsList.getCount();
}

void allyArmy::printArmy()
{
	if (saverUnitsList.getCount() != 0) {

		std::cout << "====================== Ally Army Alive Units ====================== " << endl;
		std::cout << saverUnitsList.getCount() << " SU ";
		saverUnitsList.print();
		std::cout << endl;
	}
}

void allyArmy::printFightingUnits()
{
	if (SU_attack && SU_attacking_list && !SU_attacking_list->isEmpty()) {
		std::cout << "SU " << SU_attack->getID() << " Shots ";
		SU_attacking_list->print();
	}
	delete SU_attacking_list;

	SU_attacking_list = nullptr;
}
void allyArmy::Armyfile(fstream& Output, int Df, int Dd, int SU_dead, int ET_dead, int EG_dead, int HU_dead)
{
	Output << std::fixed << std::setprecision(2);
	Output << saverUnitsList.getCount() << " SU " << endl;
	Output << endl;
	Output << (((saverUnitsList.getCount() + SU_dead) != 0) ? (double(SU_dead) / (saverUnitsList.getCount() + SU_dead)) * 100 : 
		      0 ) << " %(Dead_SU) " << endl;
	Output << endl;
	Output << ((((saverUnitsList.getCount() + SU_dead)) != 0) ?  (double(SU_dead) / (saverUnitsList.getCount() + SU_dead)) * 100 : 0 )
		   << " %(Dead_AllyUnits)" << endl;
	Output << endl;
	int sum = SU_dead ;
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
