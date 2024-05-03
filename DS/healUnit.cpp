#include "healUnit.h"

healUnit::healUnit(int id, int jointime, double health, double power, int attackcapacity) :Unit(id, "HU", jointime, health, power, attackcapacity)
{

}

void healUnit::attack(Unit* target)
{
	double healthImprovement = (Power * (Health/100)) / (pow(target->getHealth(), 0.5));
	target->setHealth(target->getHealth() + healthImprovement);
}

