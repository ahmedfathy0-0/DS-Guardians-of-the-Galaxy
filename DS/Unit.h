#ifndef UNIT_EA
#define UNIT_EA
#include <iostream>
using namespace std;
#include <string>

#include "LinkedQueue.h"

class Game;
class Army;
class Unit {

protected:

	// Data Members
	int ID;
	string Type; 
	double Health;
	double Power; 
	int attackCapacity; 

	// Battle Related Data Members

	int joinTime; //time at which unit joins the battle
	int fAtime;   // First Attack time
	int DEStime;  //Destruction time 

	// Heal-Unit Related functions
	int UMLJoinTime; 
	double originalHealth; 


	// bonus realted
	bool infected;
	bool immune;
	int healingCounter;

public:

	// Constructors and Destructors
	Unit();
	Unit(int id, string type, int jointime, double health, double power, int attackcapacity);
	~Unit();


	// Setters and Getters

	void setID(int);
	int getID() const;

	void setfatime(int);
	int getfatime() const;

	string getType() const;

	void setJoinTime(int);
	int getJoinTime() const;

	void setDEStime(int);
	int getDEStime() const;

	void setHealth(double health);
	double getHealth() const;

	void setPower(double);
	double getPower() const;

	void setAttackCapacity(int);
	int getAttackCapacity() const;
	
	double getPriority() const;//for Gunnery Units

	void setUMLJoinTime(int);
	int getUMLJoinTime() const;

	double getOriginalHealth() const;

	// Battle Related Functions
	
	virtual void attack( LinkedQueue <Unit *>* SoldierTemp, int timestep , Game * pGame , Army *enemy ) = 0; //attack another unit

	// Other Functions
	virtual void print(); //print the unit details

	friend std::ostream& operator<<(std::ostream& os, const Unit* item);

	// bonus related functions
	static int infectedCount;
	static int total_infected; //even if the soldier is dead, it is counted as infected

	void setInfectionStatus(bool);
	bool getInfectionStatus() const;

	static void decrementInfectedCount();
	static void incrementInfectedCount();
	
	static int getInfectedCount();
	static int getTotalInfected();

	void setImmunityStatus(bool);
	bool getImmunityStatus() const;

	void setHealingCounter(int);
	int getHealingCounter() const;

};
#endif

