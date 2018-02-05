/**
	@file	ChoreDatabase.cpp
	implementation file for the ChoreDatabase class
	@author	Brady Helkenn
	@date	11/08/2014
*/
#include<fstream>
#include"ChoreDatabase.h"
#include"getInt.h"
#include"Clear.h"
#include"Pause.h"
using namespace std;

//default constructor to create an empty database
ChoreDatabase::ChoreDatabase() {
	choreCount = 0;
}

//DISPLAY FUNCTIONS
/**
	displays detailed information about every chore in chores array
	@post	no member variables are modified
*/
void ChoreDatabase::displayAllChores() {
	Clear();
	for (int i = 0; i < choreCount; i++) {
		cout << "Chore #" << i + 1 << ":" << endl;
		cout << "Name: " << chores[i].getName() << endl;
		cout << "Frequency: " << chores[i].getFrequency() << endl;
		cout << "Completed: " << chores[i].getDateComplete() << endl;
		cout << "Note: " << chores[i].getNote() << endl << endl;
	}
	Pause();
}
/**
	displays detailed information about incomplete chores in chores array
	@post	no member variables are modified
*/
void ChoreDatabase::displayOutstandingChores() {
	Clear();
	int number = 1;
	for (int i = 0; i < choreCount; i++) {
		if (!chores[i].isComplete()) {
			cout << "Chore #" << number << ":" << endl;
			cout << "Name: " << chores[i].getName() << endl;
			cout << "Frequency: " << chores[i].getFrequency() << endl;
			cout << "Completed: No" << endl;
			cout << "Note: " << chores[i].getNote() << endl << endl;
			number++;
		}
	}
	Pause();
}
/**
	displays a numbered list of chore names in the array, typically for user input
	@post	chores is unchanged
*/
void ChoreDatabase::displayNumberedChoreNames() {
	for (int i = 0; i < choreCount; i++) {
		cout << i + 1 << ". " << chores[i].getName() << endl;
	}
}
//END DISPLAY FUNCTIONS

//FILE OPERATION FUNCTIONS
/**
	takes existing database and saves chore contents to a file
	@post	#1. file "database.txt" is created
			#2. file "database.txt" contains chores array contents
			#3. each chore object is represented as name, frequency, notes, and complete values
				all on one line per object, separated by semicolons (;)
*/
void ChoreDatabase::saveDatabase() {
	fstream file;
	
	if (choreCount > 0) {
		Clear();
		cout << "Saving database..." << endl;
		
		//satisfies post condition #1
		file.open("database.txt", fstream::out);
		
		//satisfies post conditions #2, #3
		for (int i = 0; i < choreCount; i++) {
			file << chores[i].getName() << ";"
			<< chores[i].getFrequency() << ";"
			<< chores[i].getNote() << ";"
			<< chores[i].getDateComplete() << ";"
			<< endl;
		}
		
		//closes file to prevent issues
		file.close();
		
		cout << "...saved." << endl;
	}
	else {
		cout << "Nothing to save!" << endl;
	}
	Pause();
}
/**
	@pre	"database.txt" file exists
	@post	chores array contains chore objects corresponding 
			to each line in "database.txt"
*/
void ChoreDatabase::loadDatabase() {
	fstream file;
	
	//ensures that multiple "loads" behave the same
	choreCount = 0;
	
	file.open("database.txt");
	//determines array size
	while (file.good()) {
		string in;
		getline(file, in);
		if (in != "")
			choreCount++;
	}
	file.close();
	
	if (choreCount > 0) {
		//sizes chores array as appropriate
		chores = new Chore[choreCount];
		
		cout << "\nLoading database..." << endl;
		
		file.open("database.txt");
		//satisfies post condition
		for (int i = 0; i < choreCount; i++) {
			string in;
			
			//gets name and sets it in the chore object
			getline(file, in, ';');
			chores[i].setName(in);
			//gets frequency and sets it in the chore object
			getline(file, in, ';');
			chores[i].setFrequency(in);
			//gets note and sets it in the chore object
			getline(file, in, ';');
			chores[i].setNote(in);
			//gets complete and sets it in the chore object
			getline(file, in, ';');
			if (in == "No")
				chores[i].setComplete(false);
			else {
				chores[i].setComplete(true);
				chores[i].setDateCompleteFromFile(in);
			}
			
			//navigates to the next line
			getline(file, in);
		}
		file.close();
		
		cout << "...loaded." << endl;
		Pause();
	}
}
//END FILE OPERATION FUNCTIONS

/**
	creates a chore and stores it within chores pointer array
	@post	#1. choreCount is incremented by 1
			#2. chores is resized to 1 larger than previous size
			#3. chores contains all pre-existing Chore items
			#4. chores contains a new user-input Chore item in the last index position
*/
void ChoreDatabase::createChore() {
	Clear();
	string name, frequency;
	cout << "Welcome to the Create-A-Chore wizard!" << endl;
	cout << "\nPlease give your new chore a name: ";
	getline(cin, name);
	cout << "Now, please choose a frequency for '" << name << "':" << endl;
	cout << "1. Daily" << endl;
	cout << "2. Weekly" << endl;
	cout << "3. Monthly" << endl;
	int choice = getInt();
	
	//enforces that 1 <= choice <= 3
	while (choice < 1 || choice > 3) {
		cout << "Please enter a value between 1 and 3: " << endl;
		choice = getInt();
	}
	
	switch (choice) {
		case 1:
			frequency = "Daily";
			break;
		case 2:
			frequency = "Weekly";
			break;
		case 3:
			frequency = "Monthly";
			break;
		default:
			break;
	}
	
	//assuming an empty database
	if (choreCount == 0) {
		//creates the first item in the array, satisfies post conditions #2, #4
		chores = new Chore(name, frequency);
	}
	//if not empty
	else {
		//create temp array for existing chores
		//necessary to satisfy post condition #3
		Chore* temp = new Chore[choreCount];
		
		//copy items from chores into temp
		for (int i = 0; i < choreCount; i++) {
			temp[i] = chores[i];
		}
		
		//satisfies post condition #2
		chores = new Chore[choreCount + 1];
		
		//satisfies post condition #3
		for (int i = 0; i < choreCount; i++) {
			chores[i] = temp[i];
		}
		
		//satisfies post condition #4
		chores[choreCount] = Chore(name, frequency);
	}
	
	//satisfies post condition #1
	choreCount++;
	
	cout << "'" << name << "' has been created with a " << frequency << " frequency." << endl;
	Pause();
}

/**
	returns size of database
	@post	choreCount is unchanged
	@return	choreCount = size of chores array
*/
int ChoreDatabase::getChoreCount() {
	return choreCount;
}

/**
	collects a note and sends it to the chore object to set the note
	@param	position = index position of chore to modify
*/
void ChoreDatabase::addNote(int position) {
	cout << "Please enter a note (single line only) to store in '" << chores[position].getName() << "': ";
	string note;
	getline(cin, note);
	chores[position].setNote(note);
	
	cout << "Note added!" << endl;
	Pause();
}

/**
	marks chore at specific position in the chores array as complete
	@param	position = index position of chore to modify
*/
void ChoreDatabase::markComplete(int position) {
	chores[position].setComplete(true);
	chores[position].setDateComplete();
	
	cout << chores[position].getName() << " has been marked as complete!" << endl;
	Pause();
}

/**
	applies completion check on chores to see if they should be reset
*/
void ChoreDatabase::refreshStillComplete() {
	for (int i = 0; i < choreCount; i++) {
		chores[i].refreshStillComplete();
	}
}