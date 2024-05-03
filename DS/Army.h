#ifndef ARMY_H 
#define ARMY_H
#include <iostream>
#include "DoubleEndedQueue.h"
#include "ArrayStack.h"
#include "DoubleQueue.h"
#include "LinkedQueue.h"
#include "priQueue.h"
#include "ArrayOfPointer.h"
#include "Unit.h"
//#include "Game.h"
using namespace std;

class Game;

class Army
{
protected:
	Game* pGame;

public:

	// Constructor and Destructor
	Army(Game*);
	~Army() {}


	// Battle related functions

	virtual void attack(Army* enemy,int timestep) = 0;
	virtual void addUnit(Unit*) = 0;
	virtual Unit* removeUnit(string) = 0;
	virtual int getSoldiersCount() = 0;

	//other functions
		
	virtual void printArmy() = 0;
	virtual void printFightingUnits() = 0;
	virtual void Armyfile(fstream&,int,int,int,int,int) = 0;

};

#endif