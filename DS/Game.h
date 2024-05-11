#ifndef GAME_EA
#define GAME_EA
#include <fstream>
#include "Army.h"
#include"allyArmy.h"
#include "RandGenerator.h"

class Game
{
	Army* alienarmy;
	Army* eartharmy;
	Army* allyarmy;
	LinkedQueue <Unit*> KilledList;
	int ES_dead, ET_dead, EG_dead, HU_dead , AS_dead, AM_dead, AD_dead,SU_dead;
	int E_Df, E_Dd,A_Df,A_Dd,Ay_Dd,Ay_Df;
	RandGenerator* pRandGen;
	int timestep;
	fstream* Input;
	fstream Output;

	// bonus related

	int infectionProb;
	int infectionthreshold;

public:
	Game();
	Game(fstream& input);
	void AddToKilled(Unit * Dead);
	void LoadParameters(fstream& input);
	void GenerateArmy();
	Army* getEarthArmy();
	Army* getAlienArmy();
	void print();
	bool StartWar();
	int getInfectionProb();
	~Game();
};
#endif



