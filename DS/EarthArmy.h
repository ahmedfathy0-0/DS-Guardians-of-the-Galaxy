#ifndef EARTH_ARMY_H 
#define EARTH_ARMY_H
#include "Army.h"



class EarthArmy : public Army
{
	LinkedQueue<Unit*> eSoldiersList;
	ArrayStack<Unit*> eTanksList;
	priQueue<Unit*> eGunneryList;
	ArrayStack<Unit*> healList;
	LinkedQueue<Unit*> tankUML;
	priQueue<Unit*> soldiersUML;
	Unit* EarthUnit;
	Unit* ES_Attack, * ET_Attack, * EG_Attack;
	LinkedQueue<Unit*>* ES_attacking_list, * ET_attacking_list, * EG_attacking_list;
	bool doneHealing;
public:
	EarthArmy(Game* pGame);
	bool attack(Army* enemy, int timestep);
	void InfectionSpread();
	void addUnit(Unit*) ;
	Unit* removeUnit(string type) ;
	int getSoldiersCount();
	void printArmy();
	void modifyUML(int timeStep);
	void Heal(int timeStep);
	void printFightingUnits();
	void Armyfile(fstream&, int, int, int, int, int,int);

	double calcinfectedperc();
};
#endif
