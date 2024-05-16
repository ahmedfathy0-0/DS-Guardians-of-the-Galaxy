#ifndef RAND_GEN_H 
#define RAND_GEN_H

#include "EarthGunnery.h"
#include "EarthSoldier.h"
#include "EarthTank.h"
#include "EarthArmy.h"
#include "healUnit.h"
#include "AlienArmy.h"
#include "AlienDrone.h"
#include "AlienMonster.h"
#include "AlienSoldier.h"
#include"saverUnit.h"



class RandGenerator
{
	// ID's
	int E_ID,A_ID,SU_ID;
	
	
	// loaded parameters
	int TS,N,prob;
	int percentage[7]; // 0-HU, 1-ES, 2-ET, 3-EG, 4-AS, 5-AM, 6-AD
	int ranges[18]; // 0-R_E_L_P 1-R_E_H_P 2-R_E_L_H 3-R_E_H_H 4-R_E_L_C 5-R_E_H_C 6-R_A_L_P 7-R_A_H_P 8-R_A_L_H 9-R_A_H_H 10-R_A_L_C 11-R_A_H_C

	// Armies-pointers
	Army * eartharmy;
	Army * alienarmy;
	Army* allyarmy;

public:

	// constructor
	RandGenerator(Army *,Army*, Army*);


	// Generation Functions
	void GenerateArmy(string armytype, int ts);
	Unit* GenerateUnit(string type, int r_l_p, int r_h_p, int r_l_h, int r_h_h, int r_l_c, int r_h_c);
	int generateRandNum(int lower, int upper);

	// Setters
	void setN(int n);
	void setPer(int HU, int ES, int ET, int EG, int AS, int AM, int AD);
	void setRange(int R_E_L_P, int R_E_H_P, int R_E_L_H, int R_E_H_H, int R_E_L_C, int R_E_H_C,
				  int R_A_L_P, int R_A_H_P, int R_A_L_H, int R_A_H_H, int R_A_L_C, int R_A_H_C,
				  int R_SU_L_P, int R_SU_H_P, int R_SU_L_H, int R_SU_H_H, int R_SU_L_C, int R_SU_H_C);
	void setProb(int prob);
			
	// Destructor
	~RandGenerator();
};

#endif