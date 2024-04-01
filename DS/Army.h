#pragma once
#include <iostream>
#include "DoubleEndedQueue.h"
#include "ArrayStack.h"
#include "DoubleQueue.h"
#include "LinkedQueue.h"
#include "priQueue.h"
#include "Unit.h"

using namespace std;

class Army
{


public:

	// Constructor and Destructor
	Army();
	~Army();


	// Battle related functions

	virtual void attack(Army* enemy) = 0;
	virtual void addUnit(Unit*) = 0;
	virtual void removeUnit(Unit*) = 0;

	//other functions
		
	virtual void printArmy();
};

