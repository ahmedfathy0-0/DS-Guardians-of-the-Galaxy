#include "healUnit.h"
#include "Game.h"
#include "LinkedQueue.h"


healUnit::healUnit(int id, int jointime, double health, double power, int attackcapacity) :Unit(id, "HU", jointime, health, power, attackcapacity)
{

}

void healUnit::attack(LinkedQueue <Unit*>* SoldierTemp, int timestep, Game* pGame, Army* enemy)
{
	//Unit* target ;
	//double healthImprovement = (Power * (Health/100)) / (pow(target->getHealth(), 0.5));
	//target->setHealth(target->getHealth() + healthImprovement);

}

