#ifndef RAND_GEN_H 
#define RAND_GEN_H

#include "EarthGunnery.h"
#include "EarthSoldier.h"
#include "EarthTank.h"
#include "EarthArmy.h"
#include "AlienArmy.h"
#include "AlienDrone.h"
#include "AlienMonster.h"
#include "AlienSoldier.h"
class RandGenerator
{
	int E_ID;
	int A_ID;
	int TS; //current timestep
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
	Army* alienarmy;
	Army* eartharmy;

public:
	RandGenerator(Army* earth,Army* aliens,int ts, int n, int es, int et, int eg, int as, int am, int ad, int prob,
		int r_E_L_P, int r_E_H_P, int r_E_L_H, int r_E_H_H,int r_E_L_C, int r_E_H_C, 
		int r_A_L_P, int r_A_H_P, int r_A_L_H, int r_A_H_H, int r_A_L_C, int r_A_H_C);
	void GenerateArmy(string armytype, Army* earth);
	Unit* GenerateUnit(string type, int r_l_p, int r_h_p, int r_l_h, int r_h_h, int r_l_c, int r_h_c);
};

#endif