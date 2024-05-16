#include<iostream>
#include <cstdlib>  
#include <time.h> 
#include"ArrayStack.h"
#include"NodeWithPrev.h"
#include"StackADT.h"
#include"DoubleEndedQueue.h"
#include<fstream>
#include "Unit.h"
#include"Game.h"
#include <Windows.h>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
using namespace std;


ostream& operator<<(ostream& os, const Unit* item) {
	os << item->getID();  // Print the ID of the unit
	if (item->getType() == "ES") {
		if(item->getInfectionStatus() == true)
			os << " infected ";
	}
	return os;
}

int main() {

	string restart = "y";
	
	while (restart == "y") {
		
		// Create a game object
		Game* pGame = new Game();

		cout << endl;
		cout << endl;
		cout << "\033[1;38;5;12m";
		      cout << R"(

				   ______                         __ _                         
				  / ____/__  __ ____ _ _____ ____/ /(_)____ _ ____   _____     
				 / / __ / / / // __ `// ___// __  // // __ `// __ \ / ___/     
				/ /_/ // /_/ // /_/ // /   / /_/ // // /_/ // / / /(__  )      
				\____/ \______\__,_//_/    \__,_//_/ \__,_//_/ /_//____/       
				  ____   / __/                                                 
				 / __ \ / /_                                                   
				/ /_/ // __/                                                   
				\_______/__             ______        __                       
				 /_  __// /_   ___     / ____/____ _ / /____ _ _  __ __  __    
				  / /  / __ \ / _ \   / / __ / __ `// // __ `/| |/_// / / /    
				 / /  / / / //  __/  / /_/ // /_/ // // /_/ /_>  < / /_/ /     
				/_/  /_/ /_/ \___/   \____/ \__,_//_/ \__,_//_/|_| \__, /      
										  /____/       
                                                                                                                    

							   

		)" << endl;
	
		cout << "\033[0m";

		//leep(2000);

		pGame->StartGame();

		// Deallocate memory 
		delete pGame;

		cout << "\n\n";
		
		cout << "Do you want to play again? (y/n)" << endl;
		cin >> restart;
		while (restart != "y" && restart != "n") {
			cout << "Please enter y or n: ";
			cin >> restart;
		}
		system("CLS");
	}
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();

}
