#include "RandGenerator.h"


RandGenerator::RandGenerator(Army* earth, Army* aliens,int ts, int n, int es, int et, int eg, int as, int am, int ad, int prob, int r_E_L_P, int r_E_H_P, int r_E_L_H, int r_E_H_H, int r_E_L_C, int r_E_H_C, int r_A_L_P, int r_A_H_P, int r_A_L_H, int r_A_H_H, int r_A_L_C, int r_A_H_C)
{
	E_ID = 0;
	A_ID = 2000;
	alienarmy = aliens;
	eartharmy = earth;
	TS = ts;
	N = n;
	ES = es;
	ET = et;
	EG = eg;
	AS = as;
	AM = am;
	AD = ad;
	Prob = prob;
	R_E_L_P = r_E_L_P;
	R_E_H_P = r_E_H_P;
	R_E_L_H = r_E_L_H;
	R_E_H_H = r_E_H_H;
	R_E_L_C = r_E_L_C;
	R_E_H_C = r_E_H_C;
	R_A_L_P = r_A_L_P;
	R_A_H_P = r_A_H_P;
	R_A_L_H = r_A_L_H;
	R_A_H_H = r_A_H_H;
	R_A_L_C = r_A_L_C;
	R_A_H_C = r_A_H_C;

	GenerateArmy("Earth", earth, ts, n, es, et, eg, prob, r_E_L_P, r_E_H_P, r_E_L_H, r_E_H_H, r_E_L_C, r_E_H_C);
	GenerateArmy("Alien", aliens, ts, n, es, et, eg, prob, r_A_L_P, r_A_H_P, r_A_L_H, r_A_H_H, r_A_L_C, r_A_H_C);
}

void RandGenerator::GenerateArmy(string armytype, Army* earth, int ts, int n, int es, int et, int eg, int prob, int r_L_P, int r_H_P, int r_L_H, int r_H_H, int r_L_C, int r_H_C)
{
	if (armytype == "Earth") {
		Unit* Earth_unit;
		for (int i = 0; i < n; i++) {
			int A = 1 + (rand() % 100);
			if (A <= prob) {
				int B = 1 + (rand() % 100);
				if (B <= es) {
					Earth_unit = GenerateUnit(ts, "ES", r_L_P, r_H_P, r_L_H, r_H_H, r_L_C, r_H_C);
					earth->addUnit(Earth_unit);
				}
				else if (B <= (es + et)) {
					Earth_unit = GenerateUnit(ts, "ET", r_L_P, r_H_P, r_L_H, r_H_H, r_L_C, r_H_C);
					earth->addUnit(Earth_unit);
				}
				else {
					Earth_unit = GenerateUnit(ts, "EG", r_L_P, r_H_P, r_L_H, r_H_H, r_L_C, r_H_C);
					earth->addUnit(Earth_unit);
				}

			}
		}
	}
	else if (armytype == "Alien") {
		Unit* Alien_unit;
		for (int i = 0; i < n; i++) {
			int A = 1 + (rand() % 100);
			if (A <= prob) {
				int B = 1 + (rand() % 100);
				if (B <= es) {
					Alien_unit = GenerateUnit(ts, "AS", r_L_P, r_H_P, r_L_H, r_H_H, r_L_C, r_H_C);
					earth->addUnit(Alien_unit);
				}
				else if (B <= (es + et)) {
					Alien_unit = GenerateUnit(ts, "AM", r_L_P, r_H_P, r_L_H, r_H_H, r_L_C, r_H_C);
					earth->addUnit(Alien_unit);
				}
				else {
					Alien_unit = GenerateUnit(ts, "AD", r_L_P, r_H_P, r_L_H, r_H_H, r_L_C, r_H_C);
					earth->addUnit(Alien_unit);
				}

			}
		}
	}
}

Unit* RandGenerator::GenerateUnit(int timestep, string type, int r_l_p, int r_h_p, int r_l_h, int r_h_h, int r_l_c, int r_h_c)
{
	Unit* Army_unit;
	int power = r_l_p + rand() % (r_h_p - r_l_p + 1);
	int health = r_l_h + rand() % (r_h_h - r_l_h + 1);
	int attack_capacity = r_l_c + rand() % (r_h_c - r_l_c + 1);

	if (type == "ES") {
		Army_unit = new EarthSoldier(E_ID++, timestep, health, power, attack_capacity);
	}
	else if (type == "ET")
	{
		Army_unit = new EarthTank(E_ID++, timestep, health, power, attack_capacity);
	}
	else if (type == "EG")
	{
		Army_unit = new EarthGunnery(E_ID++, timestep, health, power, attack_capacity);
	}
	else if (type == "AS")
	{
		Army_unit = new AlienSoldier(A_ID++, timestep, health, power, attack_capacity);
	}
	else if (type == "AM")
	{
		Army_unit = new AlienMonster(A_ID++, timestep, health, power, attack_capacity);
	}
	else if (type == "AD")
	{
		Army_unit = new AlienDrone(A_ID++, timestep, health, power, attack_capacity);
	}
	return Army_unit;
}
