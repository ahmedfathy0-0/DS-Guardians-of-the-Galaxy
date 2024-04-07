#include<iostream>
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
std::ostream& operator<<(std::ostream& os, const Unit*& item) {
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

		if (InputFile.is_open()) {
			pGame->GenereteArmy();
		}

		int randX = 1 + (rand() % 100);

		if (randX < 10) {
			pUnit = eArmy->removeUnit("ES");
			eArmy->addUnit(pUnit);
		}

		else if (randX < 20) {
			pUnit = eArmy->removeUnit("ET");
			pGame->AddToKilled(pUnit);
		}

		else if (randX < 30) {
			pUnit = eArmy->removeUnit("EG");
			double health = pUnit->getHealth();
			pUnit->setHealth(health / 2);
			eArmy->addUnit(pUnit);
		}

		else if (randX < 40) {
			double health;
			LinkedQueue<Unit*>* pQueue = new LinkedQueue<Unit*>;
			for (int i = 0; i < 5; i++) {
				pUnit = aArmy->removeUnit("AS");
				health = pUnit->getHealth();
				pUnit->setHealth(health / 2);
				pQueue->enqueue(pUnit);
				aArmy->addUnit(pUnit);
			}
		}

		else if (randX < 50) {
			for (int i = 0; i < 5; i++) {
				pUnit = aArmy->removeUnit("AM");
				aArmy->addUnit(pUnit);
			}
		}

		else if (randX < 60) {
			for (int i = 0; i < 6; i++) {
				pUnit = aArmy->removeUnit("AD");
				pGame->AddToKilled(pUnit);
			}
		}

		pGame->print();

		cout << "Press any key to continue: ";
		cin >> key;	
	}
	

}