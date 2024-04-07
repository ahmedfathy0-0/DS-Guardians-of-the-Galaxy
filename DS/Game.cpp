#include "Game.h"
#include "RandGenerator.h"
Game::Game()
{
	timestep = 0;
	eartharmy = NULL;
	alienarmy = NULL;
}
Game::Game(Army* e, Army* a)
{
	timestep = 0;
	eartharmy = e;
	alienarmy = a;
}

Game::Game(fstream& input, Army* e, Army* a)
{
	timestep = 0;
	eartharmy = e;
	alienarmy = a;
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
	timestep++;
	LoadParameters(*Input);
	RandGenerator(eartharmy,alienarmy,timestep, N, ES, ET, EG, AS, AM, AD, Prob,
		R_E_L_P, R_E_H_P, R_E_L_H, R_E_H_H, R_E_L_C, R_E_H_C,
		R_A_L_P, R_A_H_P, R_A_L_H, R_A_H_H, R_A_L_C, R_A_H_C);
}

void Game::print()
{
	cout << "Current Time Step: " << timestep << endl;

	eartharmy->printArmy();
	alienarmy->printArmy();

	std::cout << "====================== Killed / Destructed Units ====================== " << endl;
	Unit* pUnit = nullptr;
	KilledList.print();

	cout << endl;

}

