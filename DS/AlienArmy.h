#ifndef ALIEN_ARMY_H 
#define ALIEN_ARMY_H
#include "Army.h"



class AlienArmy : public Army
{

	// Army_Lists
	LinkedQueue<Unit*> aSoldiersList;
	Array<Unit*> aMonstersList; 
	DoubleEndedQueue<Unit*> aDronesList;

	//unit-pointrs 
	Unit* AlienUnit;
	Unit* AS_Attack, * AM_Attack, * AD_Attack, * AD2_Attack;
	
	//Printing related lists
	LinkedQueue<Unit*>* AS_attacking_list, * AM_attacking_list, * AD_attacking_list, * AD2_attacking_list;


	bool flag; //flag used in remove Unit to make it easy to remove drones
public:
	// Constructor
	AlienArmy(Game* pGame);
	// battle related functions
	bool attack(Army* enemy, int timestep, bool& AS_total, bool& AD_total);

	// list controlling functions
	void addUnit(Unit*);
	Unit* removeUnit(string type); // index for the monster list and the Unit pointer used if type is Drone

	// Getters
	int getSoldiersCount(); // to get the number of soldiers 

	// printing functions
	void printArmy();
	void printFightingUnits();

	// outFile functions
	void Armyfile(fstream&, int, int, int, int, int,int);

	// Destructor
	~AlienArmy();
};

#endif