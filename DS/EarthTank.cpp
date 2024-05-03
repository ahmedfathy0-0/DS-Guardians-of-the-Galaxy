#include "EarthTank.h"


EarthTank::EarthTank(int id, int jointime, double health, double power, int attackcapacity) :Unit(id, "ET", jointime, health, power, attackcapacity)
{
	originalHealth = health;
}
void EarthTank::attack(Unit* target)
{
	double Damage = (Power + Health / 100) / (pow(target->getHealth(), 0.5));
	target->setHealth(target->getHealth() - Damage);
}
