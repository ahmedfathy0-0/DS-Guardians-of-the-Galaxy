#include "Game.h"

void Game::AddToKilled(Unit* Dead)
{
	KilledList.enqueue(Dead);
}
