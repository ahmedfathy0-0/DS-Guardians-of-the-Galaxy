#include "Game.h"

Game::Game()
{
	timestep = 0;
	eartharmy = NULL;
	alienarmy = NULL;
	Input = NULL;
	pRandGen = new RandGenerator(this);
	Output.open("output.txt", ios::out);
if (!Output.is_open()) {
    std::cerr << "Failed to open output.txt for writing.\n";
} else {
    Output << "Td" << "    " << "ID" << "    " << "Tj" << "    " << "Df" << "    " << "Dd" << "    " << "Db" << endl;
}
ES_dead = 0;
ET_dead = 0;
EG_dead = 0;
AS_dead = 0;
AM_dead = 0;
AD_dead = 0;
A_Dd = 0;
A_Df = 0;
E_Dd = 0;
E_Df = 0;

}

Game::Game(fstream& input)
{
	timestep = 0;
	eartharmy = new EarthArmy(this);
	alienarmy = new AlienArmy(this);
	pRandGen = new RandGenerator(this);
	Input = &input;
	Output.open("output.txt", ios::out);
	if (!Output.is_open()) {
		std::cerr << "Failed to open output.txt for writing.\n";
	}
	else {
		Output << "Td" << "    " << "ID" << "    " << "Tj" << "    " << "Df" << "    " << "Dd" << "    " << "Db" << endl;
	}
	ES_dead = 0;
	ET_dead = 0;
	EG_dead = 0;
	AS_dead = 0;
	AM_dead = 0;
	AD_dead = 0;
	A_Dd = 0;
	A_Df = 0;
	E_Dd = 0;
	E_Df = 0;
}

void Game::AddToKilled(Unit* Dead)
{
	if (dynamic_cast<EarthSoldier*>(Dead)) {
		ES_dead++;
		E_Dd = E_Dd + timestep - (Dead->getfatime());
		E_Df = E_Df + (Dead->getfatime()) - (Dead->getJoinTime());
	}
	else if (dynamic_cast<EarthTank*>(Dead)) {
		ET_dead++;
		E_Dd = E_Dd + timestep - (Dead->getfatime());
		E_Df = E_Df + (Dead->getfatime()) - (Dead->getJoinTime());
	}
	else if (dynamic_cast<EarthGunnery*>(Dead)) {
		EG_dead++;
		E_Dd = E_Dd + timestep - (Dead->getfatime());
		E_Df = E_Df + (Dead->getfatime()) - (Dead->getJoinTime());
	}
	else if (dynamic_cast<AlienSoldier*>(Dead)) {
		AS_dead++;
		A_Dd = A_Dd + timestep - (Dead->getfatime());
		A_Df = A_Df + (Dead->getfatime()) - (Dead->getJoinTime());
	}
	else if (dynamic_cast<AlienMonster*>(Dead)) {
		AM_dead++;
		A_Dd = A_Dd + timestep - (Dead->getfatime());
		A_Df = A_Df + (Dead->getfatime()) - (Dead->getJoinTime());

	}
	else if (dynamic_cast<AlienDrone*>(Dead)) {
		AD_dead++;
		A_Dd = A_Dd + timestep - (Dead->getfatime());
		A_Df = A_Df + (Dead->getfatime()) - (Dead->getJoinTime());
	}
	

	Output << timestep<<"    " << Dead->getID() << "    " << Dead->getJoinTime() << "    " << (Dead->getfatime()) - (Dead->getJoinTime()) << "    " << timestep -(Dead->getfatime()) << "    " << (timestep)- (Dead->getJoinTime()) << endl;
	KilledList.enqueue(Dead);
}

void Game::LoadParameters(fstream& input)
{
	int N;
	int HU, ES, ET, EG, AS, AM, AD, Prob, R_E_L_P, R_E_H_P , R_E_L_H , R_E_H_H , R_E_L_C , R_E_H_C,
		R_A_L_P , R_A_H_P , R_A_L_H , R_A_H_H , R_A_L_C , R_A_H_C;

	input >> N;
	input >> HU >> ES >> ET >> EG >> AS >> AM >> AD >> Prob;
	input >> R_E_L_P >> R_E_H_P >> R_E_L_H >> R_E_H_H >> R_E_L_C >> R_E_H_C;
	input >> R_A_L_P >> R_A_H_P >> R_A_L_H >> R_A_H_H >> R_A_L_C >> R_A_H_C;
	R_E_H_P *= -1;
	R_E_H_H *= -1;
	R_E_H_C *= -1;
	R_A_H_P *= -1;
	R_A_H_H *= -1;
	R_A_H_C *= -1;

	pRandGen->setN(N);
	pRandGen->setPer(HU, ES, ET, EG, AS, AM, AD);
	pRandGen->setProb(Prob);
	pRandGen->setRange(R_E_L_P, R_E_H_P, R_E_L_H, R_E_H_H, R_E_L_C, R_E_H_C,
		R_A_L_P, R_A_H_P, R_A_L_H, R_A_H_H, R_A_L_C, R_A_H_C);

}

void Game::GenerateArmy()
{
	timestep++;
	LoadParameters(*Input);
	pRandGen->GenerateArmy("Earth",timestep);
	pRandGen->GenerateArmy("Alien", timestep);
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
	std::cout << "====================== Units Fighting at current step ===================== " << endl;
	eartharmy->printFightingUnits();
	alienarmy->printFightingUnits();
	std::cout << "====================== Killed / Destructed Units ===================== " << endl;
	std::cout << KilledList.getCount() <<" ";
	KilledList.print();


	cout << endl;

}

void Game::StartWar()
{
	eartharmy->attack(alienarmy,timestep);
	alienarmy->attack(eartharmy,timestep);

	dynamic_cast<EarthArmy*>(eartharmy)->modifyUML(timestep);
	dynamic_cast<EarthArmy*>(eartharmy)->Heal(timestep);

}

Game::~Game()
{
	Output<<endl;
	Output<<endl;
	Output << "====================== Final Earth Army ===================== " << endl;
	eartharmy->Armyfile(Output,ES_dead,ET_dead,EG_dead,E_Df,E_Dd);
	Output << "====================== Final Alien Army ===================== " << endl;
	alienarmy->Armyfile(Output,AS_dead,AM_dead,AD_dead, E_Df, E_Dd);
	Output.close();
	if (!eartharmy)
		delete eartharmy;
	
	if (!alienarmy)
		delete alienarmy;

	if (!pRandGen)
		delete pRandGen;

}

