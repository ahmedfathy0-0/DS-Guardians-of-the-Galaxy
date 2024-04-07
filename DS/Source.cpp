#include<iostream>
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
std::ostream& operator<<(std::ostream& os, const Unit* item) {
	os << item->getID();  // Print the value of the item
	return os;
}
using namespace std;

int main() {
	fstream InputFile;
	InputFile.open("Test.txt");
	Army* eArmy = new EarthArmy;
	Army* aArmy = new AlienArmy;
	Game* pGame = new Game(InputFile, eArmy,aArmy);
	Unit* pUnit;

	string key;

	for (int i = 1; i <= 50; i++) {

		srand(time(0));

		if (InputFile.is_open()) {
			pGame->GenereteArmy();
		}

		int randX = 1 + (rand() % 100);

		if (randX < 10) {
			cout << "picked a ES unit and added it again" << endl;
			pUnit = eArmy->removeUnit("ES");

			if (pUnit) {
				eArmy->addUnit(pUnit);
			}
		
		}

		else if (randX < 20) {
			cout << "picked a ET unit and added it to killed list" << endl;
			pUnit = eArmy->removeUnit("ET");
			if (pUnit) {
				pGame->AddToKilled(pUnit);
			}
		
		}


		else if (randX < 30) {
			cout << "picked a EG unit and halfed it's health" << endl;
			pUnit = eArmy->removeUnit("EG");
			if (pUnit) {
				double health = pUnit->getHealth();
				pUnit->setHealth(health / 2);
				eArmy->addUnit(pUnit);
			}
			
		}

		else if (randX < 40) {
			cout << "picked a AS unit list and halfed it's health" << endl;
			double health;
			LinkedQueue<Unit*>* pQueue = new LinkedQueue<Unit*>;
			for (int i = 0; i < 5; i++) {
				pUnit = aArmy->removeUnit("AS");
				if (pUnit) {
					health = pUnit->getHealth();
					pUnit->setHealth(health / 2);
					pQueue->enqueue(pUnit);
					aArmy->addUnit(pUnit);
				}
			}
			
		}

		else if (randX < 50) {
			cout << "picked a AM unit list and added it again" << endl;
			for (int i = 0; i < 5; i++) {
				pUnit = aArmy->removeUnit("AM");
				if (pUnit) {
					aArmy->addUnit(pUnit);
				}
			}
			
		}

		else if (randX < 60) {
			cout << "picked a AD unit list and added it to killed list" << endl;
			for (int i = 0; i < 6; i++) {
				pUnit = aArmy->removeUnit("AD");
				if (pUnit) {
					pGame->AddToKilled(pUnit);
				}
			}
			
		}

		pGame->print();

		cout << "Press any key to continue: ";
		cin >> key;	

		cout << "\n####################################################################################\n" << endl;

	}
	

}