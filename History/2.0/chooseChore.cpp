/**
	@file	chooseChore.cpp
	implementation file for chooseChore.h
	@author	Brady Helkenn
	@date	11/07/2014
*/
#include"chooseChore.h"
#include"getInt.h"

/**
	@param	cd = ChoreDatabase object, passed by reference
	@return	choice = int variable set to index position, chosen by user
	@post	0 <= choice < cd.getChoreCount() (size of chores array)
*/
int chooseChore(ChoreDatabase& cd) {
	cout << "Please choose a chore below:" << endl;
	cd.displayNumberedChoreNames();
	
	//assigns cd.getChoreCount() to a variable to prevent excessive function calls
	int size = cd.getChoreCount();
	
	//gets friendly number between 1 and size and adjusts to index numbering
	int choice = getInt() - 1;
	//enforces post condition
	while (!(choice >= 0 && choice < size)) {
		cout << "Please enter a value between 1 and " << size << ": ";
		choice = getInt() - 1;
	}
	
	return choice;
}