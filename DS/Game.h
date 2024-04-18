#ifndef GAME_EA
#define GAME_EA
#include "Unit.h"
#include "LinkedQueue.h"
#include <fstream>
#include "AlienArmy.h"
#include"EarthArmy.h"
#include "RandGenerator.h"

class RandGenerator;

class Game
{
	Army* alienarmy;
	Army* eartharmy;
	LinkedQueue <Unit*> KilledList;
	RandGenerator* pRandGen;
	int timestep;
	fstream* Input;

public:
	Game();
	Game(fstream& input);
	void AddToKilled(Unit * Dead);
	void LoadParameters(fstream& input);
	void GenerateArmy();
	Army* getEarthArmy();
	Army* getAlienArmy();
	void print();
	~Game();
};
#endif

