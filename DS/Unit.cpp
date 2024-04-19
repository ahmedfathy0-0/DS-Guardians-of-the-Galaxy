#include "Unit.h"
Unit::Unit()
{
}

Unit::Unit(int id, string type, int jointime, double health, double power, int attackcapacity)
{
	ID = id;
	joinTime = jointime;
	Type = type;
	Health = health;
	Power = power;
	attackCapacity = attackcapacity;
	fAtime = 0;
	DEStime = 0;
}

void Unit::setID(int id)
{
	ID = id;
}

int Unit::getID() const
{
	return ID;
}

string Unit::getType() const
{
	return Type;
}

void Unit::setJoinTime(int jointime)
{
	joinTime = jointime;
}

int Unit::getJoinTime() const
{
	return joinTime;
}

void Unit::setHealth(double health)
{
	Health = health;
}

double Unit::getHealth() const
{
	return Health;
}

void Unit::setPower(double power)
{
	Power = power;
}

double Unit::getPower() const
{
	return Power;
}

void Unit::setAttackCapacity(int attackcapacity)
{
	attackCapacity = attackcapacity;
}

int Unit::getAttackCapacity() const
{
	return attackCapacity;
}

double Unit::getPriority() const
{
	return 0.4 * Health + 0.6 * Power;   // means i give 40% of importance to Health and 60% to power
}

void Unit::print()
{
   

}
