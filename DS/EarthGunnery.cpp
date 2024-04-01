#include "EarthGunnery.h"

EarthGunnery::EarthGunnery(int id, int jointime, double health, double power, int attackcapacity) :Unit(id, "EG", jointime, health, power, attackcapacity)
{
}



void EarthGunnery::attack(Unit* target)
{
	double Damage = (Power + Health / 100) / (pow(target->getHealth(), 0.5));
	target->setHealth(target->getHealth() - Damage);
}
