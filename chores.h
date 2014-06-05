#include<iostream>
#include<string>
#include<sstream>
using namespace std;

#ifndef CHORES_H
#define CHORES_H

class chores {
private:
//	string day;
	stringstream daily;
	stringstream weekly;
	stringstream monthly;
	stringstream all;
	string* notes;
	//number of chores
	int number;
		
	string getDaily() {return daily.str();}
	string getWeekly() {return weekly.str();}
	string getMonthly() {return monthly.str();}
	bool validateChore(string& sr, string& rem);
	char errorMenu();
	string displayNotes(string chore, int pos);

	//helper functions
	void appendTXT(string& s1, string& s2);
	void remFromTXT(string& s1, string& s2, string& rem);
	void setString(string &s);
public:
	chores(){};
	void notesMenu();
	void addNotes();
	void initChores();
	void initNotes();
	void mainMenu(char choice);
	//string getDay() {return day;}
	//void setDay(string input) {day = input;}
	void displayChores();
	void remChore(string d, string w, string m);
	void addChore(string d, string w, string m);
	void typeOfChore(char& choice);
	void resetApp();
};

#endif