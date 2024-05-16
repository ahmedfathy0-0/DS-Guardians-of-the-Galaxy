#include "Game.h"
#include <iomanip> 
#include <iostream>
using namespace std;

Game::Game()
{
	timestep = 0;
	eartharmy = new EarthArmy(this);
	alienarmy = new AlienArmy(this);
	allyarmy = new allyArmy(this);
	pRandGen = new RandGenerator(eartharmy, alienarmy, allyarmy);
	ES_dead = 0;
	ET_dead = 0;
	EG_dead = 0;
	HU_dead = 0;
	AS_dead = 0;
	AM_dead = 0;
	AD_dead = 0;
	SU_dead = 0;
	A_Dd = 0;
	A_Df = 0;
	E_Dd = 0;
	E_Df = 0;
	Ay_Dd = 0;
	Ay_Df = 0;
	SU_help = false;

}

void Game::StartGame()
{
	string fileName;
	string outFileName;

	fstream InputFile;

	int choice = 0;

	cout << "Welcome to Gaurdians of the Galaxy War Simulator ^_^" << endl << endl;
	cout << "\033[1;38;5;12m";

	cout << "1. Weak Earth ---- Weak Aliens" << endl;
	cout << "2. Weak Earth ---- moderate Aliens" << endl;
	cout << "3. Weak Earth ---- Strong Aliens" << endl << endl;
	cout << "\033[0m";
	cout << "\033[1;38;5;10m";
	cout << "4. Strong Earth ---- Weak Aliens" << endl;
	cout << "5. Strong Earth ---- Moderate Aliens" << endl;
	cout << "6. Strong Earth ---- Strong Aliens" << endl << endl;
	cout << "\033[0m";


	cout << "Please select which case you want to simulate: " ;

	cin >> choice;
	switch  (choice) {
	case 1:
		fileName = "WE_WA";
		break;
	case 2:
		fileName = "WE_MA";
		break;
	case 3:
		fileName = "WE_SA";
		break;
	case 4:
		fileName = "SE_WA";
		break;
	case 5:
		fileName = "SE_MA";
		break;
	case 6:
		fileName = "SE_SA";
		break;
	default:
		fileName = "Test";
		break;
	}


	string temp = "inputs/" + fileName + ".txt";

	InputFile.open(temp);

	if (!InputFile.is_open()) {
		cerr << "Error: Could not open file " << fileName << endl;
		return;
	}

	LoadParameters(InputFile);

	outFileName = "outputs/" + fileName + "_OutputFile.txt";

	Output.open(outFileName, ios::out);

	if (!Output.is_open()) {
		std::cerr << "Failed to open output.txt for writing.\n";
	}

	else {
		Output << "+-----------+-----------+-----------+-----------+-----------+-----------+" << endl;
		Output << "| " << std::right << std::setw(5) << "Td" << std::setw(5) << ""
			<< "| " << std::setw(5) << "ID" << std::setw(5) << ""
			<< "| " << std::setw(5) << "Tj" << std::setw(5) << ""
			<< "| " << std::setw(5) << "Df" << std::setw(5) << ""
			<< "| " << std::setw(5) << "Dd" << std::setw(5) << ""
			<< "| " << std::setw(5) << "Db" << std::setw(5) << "" << " |" << endl;
		Output << "+-----------+-----------+-----------+-----------+-----------+-----------+" << endl;
	}

	string mode;
	cout << "\033[1;44mdo you need Silent Mode? (y/n)\033[0m" << endl;
	cin >> mode;

	system("CLS");

	if (mode == "y") {
		cout << "Silent Mode is on" << endl;
		cout << "Simulation Starts Now" << endl;
	}

	bool flag = true;

	string key;

	while (flag) {

		if (InputFile.is_open()) {
			GenerateArmy();
		}
		
		if (mode == "n") {
			cout << "before start the next timestep" << endl;

			print();

			// Start the war
			flag = StartWar();

			cout << "after start the next timestep" << endl;

			if (flag)
				print();

			cout << "Press 'q' to quit or any other key to continue: ";

			//cin >> key;
			
			if (key == "q") {
				break;
			}
		}
		else {
			flag = StartWar();
		}
	}
	
	if (mode == "y")
		cout << "Simulation Ends , Output file is created" << endl;

	InputFile.close();
}

bool Game::StartWar() {

	bool ES_total = false;
	bool AS_total = false;
	bool AD_total = false;
	bool EG_total = false;
	bool F1 = eartharmy->attack(alienarmy, timestep , ES_total , EG_total);
	bool F2 = alienarmy->attack(eartharmy, timestep, AS_total, AD_total);
	if (dynamic_cast<EarthArmy*>(eartharmy)->calcinfectedperc() == 0) {
		dynamic_cast<allyArmy*>(allyarmy)->Withdrawal();
		SU_help = false;
	}

	allyarmy->attack(alienarmy, timestep, ES_total, ES_total);

	if (timestep >= 40 && F1 && !F2) {
		dynamic_cast<EarthArmy*>(eartharmy)->witthdrawallUML();
		cout << endl;
		cout << endl;
		cout << "\033[1;32m";
		cout << R"(

			 _____           _   _       _____                     _ 
			|  ___|         | | | |     /  ___|                   | |
			| |__  __ _ _ __| |_| |__   \ `--.  __ ___   _____  __| |
			|  __|/ _` | '__| __| '_ \   `--. \/ _` \ \ / / _ \/ _` |
			| |__| (_| | |  | |_| | | | /\__/ / (_| |\ V /  __/ (_| |
			\____/\__,_|_|   \__|_| |_| \____/ \__,_| \_/ \___|\__,_|
                                                         
                                                         
			 )" << endl;
		cout << "\033[0m";
		return false;
	}
	
	else if (timestep >= 40 && !F1 && F2) {
		dynamic_cast<EarthArmy*>(eartharmy)->witthdrawallUML();
		cout << endl;
		cout << endl;
		cout << "\033[1;34m";
		cout << R"(

			  ___  _ _              _    _ _                                            
			 / _ \| (_)            | |  | (_)                                           
			/ /_\ \ |_  ___ _ __   | |  | |_ _ __  ___                                  
			|  _  | | |/ _ \ '_ \  | |/\| | | '_ \/ __|                                 
			| | | | | |  __/ | | | \  /\  / | | | \__ \                                 
			\_| |_/_|_|\___|_| |_|  \/  \/|_|_| |_|___/                                 
                                                                            
                                                                            
			 _____           _   _           _           _                            _ 
			|  ___|         | | | |         | |         | |                          | |
			| |__  __ _ _ __| |_| |__     __| | ___  ___| |_ _ __ ___  _   _  ___  __| |
			|  __|/ _` | '__| __| '_ \   / _` |/ _ \/ __| __| '__/ _ \| | | |/ _ \/ _` |
			| |__| (_| | |  | |_| | | | | (_| |  __/\__ \ |_| | | (_) | |_| |  __/ (_| |
			\____/\__,_|_|   \__|_| |_|  \__,_|\___||___/\__|_|  \___/ \__, |\___|\__,_|
										   __/  |           
										   |___/            

                                                                                              


)" << endl;
		cout << "\033[0m";
		return false;
	}

	else if (timestep >= 40 && ((!F1 && !F2) || (ES_total && AD_total) || (EG_total && AS_total))) {
		dynamic_cast<EarthArmy*>(eartharmy)->witthdrawallUML();
		cout << endl;
		cout << endl;
		cout << "\033[1;36m";
		cout << R"(
			  ____                     _ _ 
			 |  _ \ _ __ __ ___      _| | |
			 | | | | '__/ _` \ \ /\ / / | |
			 | |_| | | | (_| |\ V  V /|_|_|
			 |____/|_|  \__,_| \_/\_/ (_|_)
                                 
			)" << endl;
		cout << "\033[0m";
		return false;
	}

	dynamic_cast<EarthArmy*>(eartharmy)->modifyUML(timestep);
	dynamic_cast<EarthArmy*>(eartharmy)->Heal(timestep);
	if (dynamic_cast<EarthArmy*>(eartharmy)->calcinfectedperc() > 0) {
		dynamic_cast<EarthArmy*>(eartharmy)->InfectionSpread();
	}

	return true;

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
	else if (dynamic_cast<healUnit*>(Dead)) {
		HU_dead++;
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
	else if (dynamic_cast<saverUnit*>(Dead)) {
		SU_dead++;
		Ay_Dd = Ay_Dd + timestep - (Dead->getfatime());
		Ay_Df = Ay_Df + (Dead->getfatime()) - (Dead->getJoinTime());
	}
	

	Output << "| " << std::right << std::setw(5) << timestep << std::setw(5) << ""
		<< "| " << std::setw(5) << Dead->getID() << std::setw(5) << ""
		<< "| " << std::setw(5) << Dead->getJoinTime() << std::setw(5) << ""
		<< "| " << std::setw(5) << (Dead->getfatime()) - (Dead->getJoinTime()) << std::setw(5) << ""
		<< "| " << std::setw(5) << timestep - (Dead->getfatime()) << std::setw(5) << ""
		<< "| " << std::setw(5) << (timestep)-(Dead->getJoinTime()) << std::setw(5) << "" << " |" << endl;
	Output << "+-----------+-----------+-----------+-----------+-----------+-----------+" << endl;

	KilledList.enqueue(Dead);
}

void Game::LoadParameters(fstream& input)
{
	int N;
	int HU, ES, ET, EG, AS, AM, AD, Prob, R_E_L_P, R_E_H_P , R_E_L_H , R_E_H_H , R_E_L_C , R_E_H_C,
		R_A_L_P , R_A_H_P , R_A_L_H , R_A_H_H , R_A_L_C , R_A_H_C, R_SU_L_P, R_SU_H_P, R_SU_L_H,
		R_SU_H_H, R_SU_L_C, R_SU_H_C;
	

	input >> N;
	input >> HU >> ES >> ET >> EG >> AS >> AM >> AD >> Prob;
	input >> R_E_L_P >> R_E_H_P >> R_E_L_H >> R_E_H_H >> R_E_L_C >> R_E_H_C;
	input >> R_A_L_P >> R_A_H_P >> R_A_L_H >> R_A_H_H >> R_A_L_C >> R_A_H_C;
	input >> R_SU_L_P >> R_SU_H_P >> R_SU_L_H >> R_SU_H_H >> R_SU_L_C >> R_SU_H_C;
	input >> infectionProb;
	input >> infectionthreshold;
	R_E_H_P *= -1;
	R_E_H_H *= -1;
	R_E_H_C *= -1;
	R_A_H_P *= -1;
	R_A_H_H *= -1;
	R_A_H_C *= -1;
	R_SU_H_P *= -1;
	R_SU_H_H *= -1;
	R_SU_H_C *= -1;

	pRandGen->setN(N);
	pRandGen->setPer(HU, ES, ET, EG, AS, AM, AD);
	pRandGen->setProb(Prob);
	pRandGen->setRange(R_E_L_P, R_E_H_P, R_E_L_H, R_E_H_H, R_E_L_C, R_E_H_C,
					   R_A_L_P, R_A_H_P, R_A_L_H, R_A_H_H, R_A_L_C, R_A_H_C, R_SU_L_P, R_SU_H_P, R_SU_L_H,
					   R_SU_H_H, R_SU_L_C, R_SU_H_C);
	 
}

void Game::GenerateArmy()
{
	timestep++;
	pRandGen->GenerateArmy("Earth",timestep);
	pRandGen->GenerateArmy("Alien", timestep);

	if (dynamic_cast<EarthArmy*>(eartharmy)->calcinfectedperc() >= infectionthreshold || SU_help) {
		pRandGen->GenerateArmy("Ally", timestep);
		SU_help = true;
	}
}

Army* Game::getEarthArmy()
{
	return eartharmy;
}

Army* Game::getAlienArmy()
{
	return alienarmy;
}
Army* Game::getAllyArmy()
{
	return allyarmy;
}
int Game::getInfectionProb()
{
	return infectionProb;
}


void Game::print()
{
	cout << "Current Time Step: " << timestep << endl;

	eartharmy->printArmy();
	alienarmy->printArmy();
	allyarmy->printArmy();	

	std::cout << endl;
	std::cout << "\033[6;46m============================================ \033[0m" << endl;
	std::cout << "\033[6;46m======\033[0m \033[36mUnits Fighting at current step\033[0m \033[6;46m====== \033[0m" << endl;
	std::cout << "\033[6;46m============================================ \033[0m" << endl;
	std::cout << endl;
	std::cout << "\033[1;32m";
	eartharmy->printFightingUnits();
	std::cout << "\033[0m";
	std::cout << "\033[1;34m";
	alienarmy->printFightingUnits();
	std::cout << "\033[0m";
	std::cout << "\033[38;2;255;165;0m";
	allyarmy->printFightingUnits();
	std::cout << "\033[0m";
	std::cout << endl;
	std::cout << "\033[6;48;2;169;169;169m=============================================== \033[0m" << endl;
	std::cout << "\033[6;48;2;169;169;169m==========\033[0m \033[38;2;169;169;169mKilled / Destructed Units\033[0m \033[6;48;2;169;169;169m========== \033[0m" << endl;
	std::cout << "\033[6;48;2;169;169;169m=============================================== \033[0m" << endl;
	std::cout << endl;
	std::cout << "\033[38;2;169;169;169m";
	std::cout << KilledList.getCount() <<" ";
	KilledList.print();
	std::cout << "\033[0m";

	cout << endl;

}

Game::~Game()
{
	Output<<endl;
	Output<<endl;
	Output << "====================== Final Earth Army ===================== " << endl;
	eartharmy->Armyfile(Output,E_Df,E_Dd, ES_dead, ET_dead, EG_dead, HU_dead);
	Output << "====================== Final Alien Army ===================== " << endl;
	alienarmy->Armyfile(Output, A_Df, A_Dd, AS_dead, AM_dead, AD_dead,0);
	Output << "====================== Final Ally Army ===================== " << endl;
	allyarmy->Armyfile(Output, Ay_Df, Ay_Dd, SU_dead, ET_dead, EG_dead, HU_dead);
	Output.close();
	Unit::total_infected= 0;
	Unit::infectedCount = 0;
	if (!eartharmy)
		delete eartharmy;
	
	if (!alienarmy)
		delete alienarmy;

	if (!pRandGen)
		delete pRandGen;

}

