#ifndef ALIEN_ARMY_H 
#define ALIEN_ARMY_H
#include "Army.h"



class AlienArmy : public Army
{

	LinkedQueue<Unit*> aSoldiersList;
	Array<Unit*> aMonstersList; //for monsters
	DoubleEndedQueue<Unit*> aDronesList;
	Unit* AlienUnit;
	bool flag; //flag used in remove Unit to make it easy to remove drones
public:
	AlienArmy(Game* pGame);
	void attack(Army* enemy);
	void addUnit(Unit*);
	Unit* removeUnit(string type); // index for the monster list and the Unit pointer used if type is Drone
	void printArmy();
};

#endif