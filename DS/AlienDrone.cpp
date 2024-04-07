#include "AlienDrone.h"
AlienDrone::AlienDrone(int id, int jointime, double health, double power, int attackcapacity) :Unit(id, "AD", jointime, health, power, attackcapacity)
{
}
void AlienDrone::attack(Unit* target)
{
	double Damage = (Power + Health / 100) / (pow(target->getHealth(), 0.5));
	target->setHealth(target->getHealth() - Damage);
}
