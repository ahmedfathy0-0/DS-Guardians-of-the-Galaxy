#include<iostream>
#include"ArrayStack.h"
#include"NodeWithPrev.h"
#include"StackADT.h"
#include"DoubleEndedQueue.h"
#include<fstream>
//#include "Unit.h"
//#include"Army.h"
#include"Game.h"
//#include"AlienArmy.h"
//#include"EarthArmy.h"
std::ostream& operator<<(std::ostream& os, const Unit*& item) {
	os << item->getID();  // Print the value of the item
	return os;
}
using namespace std;
int main() {
	fstream InputFile;
	InputFile.open("Test.txt");
	Army* Eartharmy = new EarthArmy;
	Army* Alienarmy = new AlienArmy;
	Game* pGame = new Game(InputFile, Eartharmy,Alienarmy);
	

	if (InputFile.is_open()){
		pGame->LoadParameters(InputFile);
		pGame->GenereteArmy();
	}






}