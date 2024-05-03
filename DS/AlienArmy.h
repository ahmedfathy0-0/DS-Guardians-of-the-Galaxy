#ifndef ALIEN_ARMY_H 
#define ALIEN_ARMY_H
#include "Army.h"



class AlienArmy : public Army
{

	LinkedQueue<Unit*> aSoldiersList;
	Array<Unit*> aMonstersList; //for monsters
	DoubleEndedQueue<Unit*> aDronesList;
	Unit* AlienUnit;
	Unit* AS_Attack, * AM_Attack, * AD_Attack, * AD2_Attack;
	LinkedQueue<Unit*>* AS_attacking_list, * AM_attacking_list, * AD_attacking_list, * AD2_attacking_list;
	bool flag; //flag used in remove Unit to make it easy to remove drones
public:
	AlienArmy(Game* pGame);
	void attack(Army* enemy, int timestep);
	void addUnit(Unit*);
	Unit* removeUnit(string type); // index for the monster list and the Unit pointer used if type is Drone
	int getSoldiersCount(); // to get the number of soldiers 
	void printArmy();
	void printFightingUnits();
	void Armyfile(fstream&, int, int, int, int, int);
};

#endif