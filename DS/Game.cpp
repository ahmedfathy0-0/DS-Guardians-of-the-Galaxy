#include "Game.h"
#include "RandGenerator.h"
Game::Game()
{
}

Game::Game(fstream& input)
{
	alienarmy = new AlienArmy(this);
	eartharmy = new EarthArmy(this);
	Input = &input;
}

void Game::AddToKilled(Unit* Dead)
{
	KilledList.enqueue(Dead);
}

void Game::LoadParameters(fstream& input)
{
	input >> N;
	input >> ES >> ET >> EG >> AS >> AM >> AD >> Prob;
	input >> R_E_L_P >> R_E_H_P >> R_E_L_H >> R_E_H_H >> R_E_L_C >> R_E_H_C;
	input >> R_A_L_P >> R_A_H_P >> R_A_L_H >> R_A_H_H >> R_A_L_C >> R_A_H_C;
	R_E_H_P *= -1;
	R_E_H_H *= -1;
	R_E_H_C *= -1;
	R_A_H_P *= -1;
	R_A_H_H *= -1;
	R_A_H_C *= -1;
}

void Game::GenereteArmy()
{
	LoadParameters(*Input);
	RandGenerator(eartharmy,alienarmy,timestep, N, ES, ET, EG, AS, AM, AD, Prob,
		R_E_L_P, R_E_H_P, R_E_L_H, R_E_H_H, R_E_L_C, R_E_H_C,
		R_A_L_P, R_A_H_P, R_A_L_H, R_A_H_H, R_A_L_C, R_A_H_C);
	
}
