#ifndef GAME_EA
#define GAME_EA
#include <fstream>
#include "Army.h"
#include"allyArmy.h"
#include "RandGenerator.h"
#include "LinkedQueue.h"


class Game
{

	// Armies 
	Army* alienarmy;
	Army* eartharmy;
	Army* allyarmy;


	LinkedQueue <Unit*> KilledList;

	// statistics related parameters
	int ES_dead, ET_dead, EG_dead, HU_dead , AS_dead, AM_dead, AD_dead,SU_dead;
	int E_Df, E_Dd,A_Df,A_Dd,Ay_Dd,Ay_Df;

	// Generation dataMembers
	RandGenerator* pRandGen;
	int timestep;

	// input/output 
	fstream* Input;
	fstream Output;

	// bonus related
	int infectionProb;
	int infectionthreshold;
	bool SU_help;  // to check if the ally army is helping the earth army

public:

	// Constructor
	Game();

	// battle related functions
	void GenerateArmy();
	void AddToKilled(Unit * Dead);
	bool StartWar();
	void StartGame();

	// input functions
	void LoadParameters(fstream& input);
	
	// geters
	Army* getEarthArmy();
	Army* getAlienArmy();
	Army* getAllyArmy();
	int getInfectionProb();

	//print function
	void print();

	// destructor
	~Game();
};

#endif



