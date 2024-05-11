#include "RandGenerator.h"


int RandGenerator::E_ID = 0;
int RandGenerator::A_ID = 2000;
int RandGenerator::SU_ID = 4000;

RandGenerator::RandGenerator(Army* Earth , Army* Alien, Army* Ally)
{
	
	eartharmy = Earth;
	alienarmy = Alien;
	allyarmy = Ally;

}

void RandGenerator::GenerateArmy(string armytype,int ts)
{
	TS = ts;

	srand(time(0));


	if (armytype == "Earth") {
		Unit* Earth_unit;
		for (int i = 0; i < N; i++) {
			int A = 1 + (rand() % 100);
			if (A <= prob) {
				int B = 1 + (rand() % 100);
				if (B <= percentage[0]) {
					Earth_unit = GenerateUnit("HU", ranges[0], ranges[1], ranges[2], ranges[3], ranges[4], ranges[5]);
					eartharmy->addUnit(Earth_unit);
				}
				else if (B <= (percentage[0] + percentage[1])) {
					Earth_unit = GenerateUnit("ES", ranges[0], ranges[1], ranges[2], ranges[3], ranges[4], ranges[5]);
					eartharmy->addUnit(Earth_unit);
				}
				else if(B <= (percentage[0] + percentage[1] + percentage[2])) {
					Earth_unit = GenerateUnit("ET", ranges[0], ranges[1], ranges[2], ranges[3], ranges[4], ranges[5]);
					eartharmy->addUnit(Earth_unit);
				}
				else {
					Earth_unit = GenerateUnit("EG", ranges[0], ranges[1], ranges[2], ranges[3], ranges[4], ranges[5]);
					eartharmy->addUnit(Earth_unit);
				}

			}
		}
	}
	else if (armytype == "Alien") {
		Unit* Alien_unit;
		for (int i = 0; i < N; i++) {
			int A = 1 + (rand() % 100);
			if (A <= prob) {
				int B = 1 + (rand() % 100);
				if (B <= percentage[4]) {
					Alien_unit = GenerateUnit("AS", ranges[6], ranges[7], ranges[8], ranges[9], ranges[10], ranges[11]);
					alienarmy->addUnit(Alien_unit);
				}
				else if (B <= (percentage[4] + percentage[5])) {
					Alien_unit = GenerateUnit("AM", ranges[6], ranges[7], ranges[8], ranges[9], ranges[10], ranges[11]);
					alienarmy->addUnit(Alien_unit);
				}
				else {
					Alien_unit = GenerateUnit("AD", ranges[6], ranges[7], ranges[8], ranges[9], ranges[10], ranges[11]);
					alienarmy->addUnit(Alien_unit);
				}

			}
		}
	}
	else if (armytype == "Ally") {
		Unit* Ally_unit;
		for (int i = 0; i < N; i++) {
			int A = 1 + (rand() % 100);
			if (A <= prob) {
				Ally_unit = GenerateUnit("SU", ranges[12], ranges[13], ranges[14], ranges[15], ranges[16], ranges[17]);
				allyarmy->addUnit(Ally_unit);
			}
		}
	}
}

Unit* RandGenerator::GenerateUnit(string type, int r_l_p, int r_h_p, int r_l_h, int r_h_h, int r_l_c, int r_h_c)
{
	Unit* Army_unit=nullptr;
	int power = r_l_p + rand() % (r_h_p - r_l_p + 1);
	int health = r_l_h + rand() % (r_h_h - r_l_h + 1);
	int attack_capacity = r_l_c + rand() % (r_h_c - r_l_c + 1);

	if (type == "HU" && E_ID <=999) {
		Army_unit = new healUnit(E_ID++, TS, health, power, attack_capacity);
	}
	else if (type == "ES" && E_ID <= 999) {
		Army_unit = new EarthSoldier(E_ID++, TS, health, power, attack_capacity);
	}
	else if (type == "ET" && E_ID <= 999)
	{
		Army_unit = new EarthTank(E_ID++, TS, health, power, attack_capacity);
	}
	else if (type == "EG" && E_ID <= 999)
	{
		Army_unit = new EarthGunnery(E_ID++, TS, health, power, attack_capacity);
	}
	else if (type == "AS" && A_ID <= 2999)
	{
		Army_unit = new AlienSoldier(A_ID++, TS, health, power, attack_capacity);
	}
	else if (type == "AM" && A_ID <= 2999)
	{
		Army_unit = new AlienMonster(A_ID++, TS, health, power, attack_capacity);
	}
	else if (type == "AD" && A_ID <= 2999)
	{
		Army_unit = new AlienDrone(A_ID++, TS, health, power, attack_capacity);
	}
	else if (type == "SU" && SU_ID <= 4999) {
		Army_unit = new saverUnit(SU_ID++, TS, health, power, attack_capacity);
	}
	return Army_unit;
}

void RandGenerator::setN(int n)
{
	N = n;
}

void RandGenerator::setPer(int HU, int ES, int ET, int EG, int AS, int AM, int AD)
{
	percentage[0] = HU;  // HU setter
	percentage[1] = ES, percentage[2] = ET, percentage[3] = EG; // Earth Setters
	percentage[4] = AS, percentage[5] = AM, percentage[6] = AD; // Alien Setters

}

void RandGenerator::setRange(int R_E_L_P, int R_E_H_P, int R_E_L_H, int R_E_H_H, int R_E_L_C, int R_E_H_C,
	int R_A_L_P, int R_A_H_P, int R_A_L_H, int R_A_H_H, int R_A_L_C, int R_A_H_C,
	int R_SU_L_P, int R_SU_H_P, int R_SU_L_H, int R_SU_H_H, int R_SU_L_C, int R_SU_H_C)
{
	ranges[0] = R_E_L_P, ranges[1] = R_E_H_P, ranges[2] = R_E_L_H, ranges[3] = R_E_H_H, ranges[4] = R_E_L_C, ranges[5] = R_E_H_C; //Earth Ranges
	ranges[6] = R_A_L_P, ranges[7] = R_A_H_P, ranges[8] = R_A_L_H, ranges[9] = R_A_H_H, ranges[10] = R_A_L_C, ranges[11] = R_A_H_C; // Alien Ranges
	ranges[12] = R_SU_L_P, ranges[13] = R_SU_H_P, ranges[14] = R_SU_L_H, ranges[15] = R_SU_H_H, ranges[16] = R_SU_L_C, ranges[17] = R_SU_H_C; // Alien Ranges

}

void RandGenerator::setProb(int p)
{
	prob = p;
}

RandGenerator::~RandGenerator()
{
}
