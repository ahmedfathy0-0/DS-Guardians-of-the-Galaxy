#include<iostream>
#include <cstdlib>  
#include <time.h> 
#include"ArrayStack.h"
#include"NodeWithPrev.h"
#include"StackADT.h"
#include"DoubleEndedQueue.h"
#include<fstream>
#include "Unit.h"
//#include"Army.h"
#include"Game.h"
//#include"AlienArmy.h"
//#include"EarthArmy.h"
ostream& operator<<(ostream& os, const Unit* item) {
	os << item->getID();  // Print the ID of the unit
	if (item->getType() == "ES") {
		if(item->getInfectionStatus() == true)
			os << " infected ";
	}
	return os;
}
using namespace std;

int main() {

	string key;
	string mode;
	// Open the input file
	fstream InputFile;
	InputFile.open("Test.txt");
	if (!InputFile.is_open()) {
		cerr << "Error: Could not open file 'Test.txt'." << endl;
		return 1; // Exit program on error
	}
	// Create a game object
	Game* pGame = new Game(InputFile);
	bool flag = true;
	cout << "do you need Silent Mode? (y/n)" << endl;
	cin >> mode;
	system("CLS");
	if (mode == "y") {
		cout << "Silent Mode is on" << endl;
		cout <<"Simulation Starts Now"<<endl;
	}


	while (flag){
		if (InputFile.is_open()) {
			srand(time(0));
			pGame->GenerateArmy();
        }
		if (mode == "n") {
			cout << "before start the next timestep" << endl;
			pGame->print();
			// Start the war
			flag = pGame->StartWar();
			cout << "after start the next timestep" << endl;
			if(flag)
			  pGame->print();
			cout << "Press 'q' to quit or any other key to continue: ";
			//cin >> key;
			if (key == "q") {
				break;
			}
			if(flag)
			  system("CLS");
		}
		else {
			flag = pGame->StartWar();
		}
	}
	if(mode == "y")
		cout << "Simulation Ends , Output file is created" << endl;

	// Deallocate memory 
	delete pGame;

	// Close the input file
	InputFile.close();

}
