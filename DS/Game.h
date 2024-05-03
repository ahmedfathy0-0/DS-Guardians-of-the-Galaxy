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
	int ES_dead, ET_dead, EG_dead, AS_dead, AM_dead, AD_dead;
	int E_Df, E_Dd,A_Df,A_Dd;
	RandGenerator* pRandGen;
	int timestep;
	fstream* Input;
	fstream Output;

public:
	Game();
	Game(fstream& input);
	void AddToKilled(Unit * Dead);
	void LoadParameters(fstream& input);
	void GenerateArmy();
	Army* getEarthArmy();
	Army* getAlienArmy();
	void print();
	void StartWar();
	~Game();
};
#endif



