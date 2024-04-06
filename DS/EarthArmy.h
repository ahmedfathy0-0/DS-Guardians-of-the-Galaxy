#ifndef EARTH_ARMY_H 
#define EARTH_ARMY_H
#include "Army.h"



class EarthArmy : public Army
{

	LinkedQueue<Unit*> eSoldiersList;
	ArrayStack<Unit*> eTanksList;
	priQueue<Unit*> eGunneryList;
	Unit* EarthUnit;
public:
	EarthArmy(Game* pgame);
	void attack(Army* enemy) ;
	void addUnit(Unit*) ;
	Unit* removeUnit(string type) ;
	friend std::ostream& operator<<(std::ostream& os, const		Unit*& item);
	void printArmy();

};
#endif
