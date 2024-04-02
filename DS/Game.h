#ifndef GAME_EA
#define GAME_EA
#include "Unit.h"
#include "LinkedQueue.h"
class Unit;
class Game
{
	LinkedQueue <Unit*> KilledList;

	public:
		Game();
		void AddToKilled(Unit * Dead);
};
#endif

