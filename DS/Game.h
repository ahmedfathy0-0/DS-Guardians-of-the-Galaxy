#ifndef GAME_EA
#define GAME_EA
#include "Unit.h"
#include "LinkedQueue.h"
#include <fstream>
#include "AlienArmy.h"
#include"EarthArmy.h"


class Game
{
	Army* alienarmy;
	Army* eartharmy;
	LinkedQueue <Unit*> KilledList;
	int timestep;
	int N;
	int ES;
	int ET;
	int EG;
	int AS;
	int AM;
	int AD;
	int Prob;
	int R_E_L_P;
	int R_E_H_P;
	int R_E_L_H;
	int R_E_H_H;
	int R_E_L_C;
	int R_E_H_C;
	int R_A_L_P;
	int R_A_H_P;
	int R_A_L_H;
	int R_A_H_H;
	int R_A_L_C;
	int R_A_H_C;
	fstream* Input;

public:
	Game();
	Game(fstream& input);
	void AddToKilled(Unit * Dead);
	void LoadParameters(fstream& input);
	void GenereteArmy();

};
#endif

