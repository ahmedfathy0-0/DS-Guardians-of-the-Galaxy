#ifndef EARTH_ARMY_H 
#define EARTH_ARMY_H
#include "Army.h"



class EarthArmy : public Army
{

	// Army_Lists
	LinkedQueue<Unit*> eSoldiersList;
	ArrayStack<Unit*> eTanksList;
	priQueue<Unit*> eGunneryList;
	ArrayStack<Unit*> healList;

	// UML Lists
	LinkedQueue<Unit*> tankUML;
	priQueue<Unit*> soldiersUML;

	// Unit-Pointers
	Unit* EarthUnit;
	Unit* ES_Attack, * ET_Attack, * EG_Attack, * HU_Healing;

	// printig related lists
	LinkedQueue<Unit*>* ES_attacking_list, * ET_attacking_list, * EG_attacking_list, * HU_healing_list;

	// helper variables
	bool doneHealing;

public:

	// Constructor
	EarthArmy(Game* pGame);

	// battle related functions
	bool attack(Army* enemy, int timestep, bool& ES_total, bool& EG_total);
	void InfectionSpread();
	double calcinfectedperc();
	void witthdrawallUML();

	// list controlling functoins
	void addUnit(Unit*);
	Unit* removeUnit(string type);

	// Healing related functions
	void modifyUML(int timeStep);
	void Heal(int timeStep);

	// geters
	int getSoldiersCount();

	// printing functions
	void printArmy();
	void printFightingUnits();

	// outFile function
	void Armyfile(fstream&, int, int, int, int, int, int);

	// Destructor
	~EarthArmy();
};
#endif
