/**
	@file	ChoreDatabase.h
	header file for the ChoreDatabase class
	@author	Brady Helkenn
	@date	11/09/2014
*/
#include"Chore.h"
using namespace std;

#ifndef CHOREDATABASE_H
#define CHOREDATABASE_H

class ChoreDatabase {
private:
	Chore* chores;
	int choreCount;
public:
	ChoreDatabase();
	void createChore();
	void displayAllChores();
	void displayOutstandingChores();
	void displayNumberedChoreNames();
	int getChoreCount();
	void addNote(int);
	void saveDatabase();
	void loadDatabase();
	void markComplete(int);
	void refreshStillComplete();
};

#endif