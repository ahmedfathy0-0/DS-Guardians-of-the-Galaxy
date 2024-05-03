#ifndef UNIT_EA
#define UNIT_EA
#include <iostream>
using namespace std;
#include <string>

class Game;
class Unit
{
protected:
	int ID; //unique identifier for each unit
	string Type; //type of unit
	int joinTime; //time at which unit joins the battle
	int fAtime;   // First Attack time
	int DEStime;  //Destruction time 
	double Health;
	double Power; 
	int attackCapacity; 
	int UMLJoinTime; //time at which unit joins the UML
	double originalHealth; // used for tanks and soldiers
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
	
	virtual void attack( Unit* ) = 0; //attack another unit

	// Other Functions
	virtual void print(); //print the unit details

	friend std::ostream& operator<<(std::ostream& os, const Unit* item);
};
#endif

