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
	return os;
}
using namespace std;

int main() {
	string key;
	cout << "\033[1;36mBefore starting the test code,\nwe need to make sure that u know we clear the screen after \neach iteration to make the output more clear and easy to read.\n Don't worry every information u need to know will be displayed \033[0m" << endl;
	cout << "\033[1;32mPress any key to start the test code.\033[0m" << endl; /// we tried to make the text bold too but we failed:(
	cin >> key;
	// Test the ArrayStack class
	// Open the input file
	fstream InputFile;
	InputFile.open("Test.txt");
	if (!InputFile.is_open()) {
		cerr << "Error: Could not open file 'Test.txt'." << endl;
		return 1; // Exit program on error
	}
	// Create armies and game object
	Army* eArmy = new EarthArmy;
	Army* aArmy = new AlienArmy;
	Game* pGame = new Game(InputFile, eArmy,aArmy);
	Unit* pUnit;
	for (int i = 1; i <= 50; i++) {
		system("cls");  // Clear the screen
		// Print game state
		cout << i << " iterations: " << "Game state before generate units "<< endl;
		pGame->print();
		// Separator line
		cout << "\n######################################################################################\n";
		cout << "\n######################################################################################\n" << endl;



		srand(time(0));
		// Generate army if file is open
		if (InputFile.is_open()) {
			pGame->GenereteArmy();
		}
		// Print game state
		cout<< "Game state after generate units" << endl;
		pGame->print();
		// Separator line
		cout << "\n######################################################################################\n";
		cout << "\n######################################################################################\n" << endl;

		int randX = 1 + (rand() % 100);

		if (randX < 10) {
			cout << "Picked an ES unit and added it back." << endl;
			pUnit = eArmy->removeUnit("ES");

			if (pUnit) {
				eArmy->addUnit(pUnit);
			}
		
		}

		else if (randX < 20) {
			cout << "Picked an ET unit and added it to killed list." << endl;
			pUnit = eArmy->removeUnit("ET");
			if (pUnit) {
				pGame->AddToKilled(pUnit);
			}
		
		}


		else if (randX < 30) {
			cout << "Picked an EG unit and halved its health." << endl;
			pUnit = eArmy->removeUnit("EG");
			if (pUnit) {
				double health = pUnit->getHealth();
				pUnit->setHealth(health / 2);
				eArmy->addUnit(pUnit);
			}
			
		}

		else if (randX < 40) {
			cout << "Picked 5 AS units and halved their health." << endl;
			double health;
			LinkedQueue<Unit*>* pQueue = new LinkedQueue<Unit*>;
			for (int i = 0; i < 5; ++i) {
				pUnit = aArmy->removeUnit("AS");
				if (pUnit) {
					health = pUnit->getHealth();
					pUnit->setHealth(health / 2);
					pQueue->enqueue(pUnit);
					pUnit = nullptr;
				}
			}
			// Add units back to the army after processing
			while (!pQueue->isEmpty()) {
				pQueue->dequeue(pUnit);
				aArmy->addUnit(pUnit);
			}
			delete pQueue;  // Deallocate memory after use
			
		}

		else if (randX < 50) {
			cout << "Picked 5 AM units and added them back." << endl;
			for (int i = 0; i < 5; i++) {
				pUnit = aArmy->removeUnit("AM");
				if (pUnit) {
					aArmy->addUnit(pUnit);
				}
			}
			
		}

		else if (randX < 60) {
			cout << "Picked 6 AD units and added them to killed list." << endl;
			for (int i = 0; i < 6; i++) {
				pUnit = aArmy->removeUnit("AD");
				if (pUnit) {
					pGame->AddToKilled(pUnit);
				}
			}
			
		}
		else {
			cout << "No operation performed" << endl;
		}
		
		// Print game state
		cout << "Game state after processing units" << endl;
		pGame->print();
		// Separator line
		cout << "\n######################################################################################\n";
		cout << "\n######################################################################################\n" << endl;

		// Wait for  input
		cout << "Press any key to continue: ";
		string key;
		cin >> key;

		
	}

	// Deallocate memory 
	delete eArmy;
	delete aArmy;
	delete pGame;

	// Close the input file
	InputFile.close();

}
