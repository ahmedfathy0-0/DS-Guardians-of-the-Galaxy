#include "Game.h"

Game::Game()
{
	timestep = 0;
	eartharmy = NULL;
	alienarmy = NULL;
}

Game::Game(fstream& input)
{
	timestep = 0;
	eartharmy = new EarthArmy(this);
	alienarmy = new AlienArmy(this);
	pRandGen = new RandGenerator(this, timestep);
	Input = &input;
}

void Game::AddToKilled(Unit* Dead)
{
	KilledList.enqueue(Dead);
}

void Game::LoadParameters(fstream& input)
{
	int N;
	int ES, ET, EG, AS, AM, AD, Prob, R_E_L_P, R_E_H_P , R_E_L_H , R_E_H_H , R_E_L_C , R_E_H_C,
		R_A_L_P , R_A_H_P , R_A_L_H , R_A_H_H , R_A_L_C , R_A_H_C;

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

	pRandGen->setN(N);
	pRandGen->setPer(ES, ET, EG, AS, AM, AD);
	pRandGen->setProb(Prob);
	pRandGen->setRange(R_E_L_P, R_E_H_P, R_E_L_H, R_E_H_H, R_E_L_C, R_E_H_C,
		R_A_L_P, R_A_H_P, R_A_L_H, R_A_H_H, R_A_L_C, R_A_H_C);

}

void Game::GenerateArmy()
{
	timestep++;
	LoadParameters(*Input);
	pRandGen->GenerateArmy("Earth");
	pRandGen->GenerateArmy("Alien");
}

Army* Game::getEarthArmy()
{
	return eartharmy;
}

Army* Game::getAlienArmy()
{
	return alienarmy;
}

void Game::print()
{
	cout << "Current Time Step: " << timestep << endl;

	eartharmy->printArmy();
	alienarmy->printArmy();

	std::cout << "====================== Killed / Destructed Units ===================== " << endl;
	Unit* pUnit = nullptr;
	std::cout << KilledList.getCount() <<" ";
	KilledList.print();

	cout << endl;

}

Game::~Game()
{
	if (!eartharmy)
		delete eartharmy;
	
	if (!alienarmy)
		delete alienarmy;

	if (!pRandGen)
		delete pRandGen;

}

