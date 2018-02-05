/**
	@file	program.cpp
	main program file for the Chores program
	@author	Brady Helkenn
	@date	11/09/2014
*/
#include"ChoreDatabase.h"
#include"getChar.h"
#include"chooseChore.h"
#include"Clear.h"
#include"Pause.h"
using namespace std;

int main() {
	//Introduction
	cout << "Welcome to the chores program!" << endl;
	
	//Initialize database
	ChoreDatabase cd;
	
	//load saved database
	cd.loadDatabase();
	cd.refreshStillComplete();
	
	char choice = 0;
	while (!(choice == 'Q' || choice == 'q')) {
		Clear();
		cout << "Please choose an option below:" << endl;
		cout << "1. View all created chores" << endl;
		cout << "2. View all outstanding chores" << endl;
		cout << "3. Create a new chore" << endl;
		cout << "4. Add a single-line note/description to an existing chore" << endl;
		cout << "5. Mark a chore as complete" << endl;
		cout << "(S)ave chore database" << endl;
		cout << "(Q)uit the program" << endl;
		choice = getChar();
		
		switch (choice) {
			case '1':
				cd.displayAllChores();
				break;
			case '2':
				cd.displayOutstandingChores();
				break;
			case '3':
				cd.createChore();
				break;
			case '4':
				cd.addNote(chooseChore(cd));
				break;
			case '5':
				cd.markComplete(chooseChore(cd));
				break;
			case 'S':
			case 's':
				cd.saveDatabase();
				break;
			default:
				break;
		}
	}
}