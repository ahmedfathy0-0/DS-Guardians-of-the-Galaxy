#include "saverUnit.h"

saverUnit::saverUnit(int id, int jointime, double health, double power, int attackcapacity) :Unit(id, "SU", jointime, health, power, attackcapacity)
{
}

void saverUnit::attack(LinkedQueue<Unit*>* enemyTemp, int timestep, Game* pGame, Army* enemy)
{

}
