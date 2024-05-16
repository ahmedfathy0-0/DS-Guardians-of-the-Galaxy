#ifndef ARMY_H 
#define ARMY_H
#include <iostream>
#include "DoubleEndedQueue.h"
#include "ArrayStack.h"
#include "DoubleQueue.h"
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

	// Constructor 
	Army(Game*);

	// Battle related functions

	virtual bool attack(Army* enemy,int timestep,bool &,bool &) = 0;


	// list controlling functions
	virtual void addUnit(Unit*) = 0;
	virtual Unit* removeUnit(string) = 0;

	// Getters
	virtual int getSoldiersCount() = 0;


	// printing functions		
	virtual void printArmy() = 0;
	virtual void printFightingUnits() = 0;

	// outFile functions
	virtual void Armyfile(fstream&,int,int,int,int,int,int x) = 0;


	// Destructor
	virtual ~Army();

};

#endif