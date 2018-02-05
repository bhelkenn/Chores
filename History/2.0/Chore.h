/**
	@file	Chore.h
	header file for the Chore class
	@author	Brady Helkenn
	@date	11/09/2014
*/
#include<iostream>
#include<string>
using namespace std;

#ifndef CHORE_H
#define CHORE_H

class Chore {
private:
	string name;
	string frequency;
	bool complete;
	string note;
	int dateComplete[3];
public:
	Chore();
	Chore(string, string);
	string getName();
	string getFrequency();
	bool isComplete();
	string getNote();
	string getDateComplete();
	void setName(string);
	void setFrequency(string);
	void setNote(string);
	void setComplete(bool);
	void setDateComplete();
	void setDateCompleteFromFile(string);
	void refreshStillComplete();
};

#endif