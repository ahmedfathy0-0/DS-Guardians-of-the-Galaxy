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
	//Game* pGame;

public:

	// Constructor and Destructor
	Army();
	~Army() {}


	// Battle related functions

	virtual void attack(Army* enemy, Game* pGame) = 0;
	virtual void addUnit(Unit*) = 0;
	virtual Unit* removeUnit(string) = 0;

	//other functions
		
	virtual void printArmy() = 0;
};

#endif