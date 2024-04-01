#pragma once
#include <iostream>
using namespace std;
#include <string>


class Unit
{

	int ID; //unique identifier for each unit
	string Type; //type of unit
	int joinTime; //time at which unit joins the battle
	double Health;
	double Power; 
	int attackCapacity; 

public:

	// Constructors and Destructors
	Unit();
	Unit(int, string, int, int, int, int);
	~Unit();


	// Setters and Getters

	void setID(int);
	int getID() const;

	string getType() const;

	void setJoinTime(int);
	int getJoinTime() const;

	void setHealth(int);
	int getHealth() const;

	void setPower(int);
	int getPower() const;

	void setAttackCapacity(int);
	int getAttackCapacity() const;


	// Battle Related Functions
	
	virtual void attack( Unit* ) = 0; //attack another unit

	// Other Functions
	virtual void print(); //print the unit details
};

