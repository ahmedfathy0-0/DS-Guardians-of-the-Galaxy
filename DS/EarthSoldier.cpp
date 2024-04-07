#include "EarthSoldier.h"
EarthSoldier::EarthSoldier(int id, int jointime, double health, double power, int attackcapacity) :Unit(id, "ES", jointime, health, power, attackcapacity)
{
}
void EarthSoldier::attack(Unit* target)
{
	double Damage = (Power + Health / 100) / (pow(target->getHealth(), 0.5));
	target->setHealth(target->getHealth() - Damage);
}
