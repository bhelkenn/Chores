/**
	@file	Chore.cpp
	implementation file for the Chore class
	@author	Brady Helkenn
	@date	11/10/2014
*/
#include<ctime>
#include<sstream>
#include"Chore.h"
#include"Pause.h"
using namespace std;

//CONSTRUCTORS
//default constructor used for dynamic allocation
Chore::Chore() {}
/**
	standard constructor used for Chore creation
	@param	inputName = string variable initializing the name of the chore
	@param	inputType = string variable initializing the frequency of the chore
*/
Chore::Chore(string inputName, string inputFreq) {
	name = inputName;
	frequency = inputFreq;
	complete = false;
}
//END CONSTRUCTORS

//GET FUNCTIONS
/**
	returns name of the chore
	@return	name = name of the chore
*/
string Chore::getName() {
	return name;
}
/**
	returns what the frequency of the chore is, typically daily, weekly, or monthly
	@return	frequency = frequency of the chore
*/
string Chore::getFrequency() {
	return frequency;
}
/**
	returns whether or not the chore has been completed
	@return	complete = completion boolean of the chore
*/
bool Chore::isComplete() {
	return complete;
}
/**
	returns any notes associated with the chore
	@return	note = a single-line note associated with the chore
*/
string Chore::getNote() {
	return note;
}
/**
	returns dateComplete array associated with the chore
	@return	date = US-friendly representation of the dateComplete array
*/
string Chore::getDateComplete() {
	string date;
	if (complete) {
		stringstream ss;
		ss << dateComplete[1] << "-" << dateComplete[2] << "-" << dateComplete[0];
		date = ss.str();
	}
	else {
		date = "No";
	}
	return date;
}
//END GET FUNCTIONS

//SET FUNCTIONS
/**
	assigns a string value as the chore's name
	@param	inputName = string variable containing name to store in the chore object
*/
void Chore::setName(string inputName) {
	name = inputName;
}
/**
	assigns a string value as the chore's frequency
	@param	inputFreq = string variable containing frequency to store in the chore object
*/
void Chore::setFrequency(string inputFreq) {
	frequency = inputFreq;
}
/**
	assigns a string value as the chore's note
	@param	inputNote = string variable containing note to store in the chore object
*/
void Chore::setNote(string inputNote) {
	note = inputNote;
}
/**
	assigns a bool value as the chore's completion status
	@param	inputComplete = bool variable containing completion status
*/
void Chore::setComplete(bool inputComplete) {
	complete = inputComplete;
}
/**
	populates dateComplete
*/
void Chore::setDateComplete() {
	time_t t = time(0);
	struct tm now;
	localtime_s(&now, &t);
	dateComplete[0] = now.tm_year + 1900;
	dateComplete[1] = now.tm_mon + 1;
	dateComplete[2] = now.tm_mday;
}
/**
	populates dateComplete from file
	@param	date = string value of US-friendly date associated with the chore
	@post	#1. date's information is transferred into an int array
			#2. int array nums is saved in appropriate order to dateComplete array
*/
void Chore::setDateCompleteFromFile(string date) {
	stringstream ss(date);
	string input;
	int nums[3];
	
	//satisfies post condition #1
	for (int i = 0; i < 2; i++ ) {
		getline(ss, input, '-');
		stringstream parsed;
		parsed << input;
		parsed >> nums[i];
	}
	getline(ss, input);
	stringstream parsed;
	parsed << input;
	parsed >> nums[2];
	
	//satisfies post condition #2
	dateComplete[0] = nums[2];
	dateComplete[1] = nums[0];
	dateComplete[2] = nums[1];
}
//END SET FUNCTIONS

/**
	checks if chore is no longer complete based on frequency and resets if necessary
*/
void Chore::refreshStillComplete() {
	if (complete) {
		time_t t = time(0);
		struct tm now;
		localtime_s(&now, &t);
		
		double currentDate = (now.tm_year + 1900) + ((now.tm_mon + 1) / 12.0) + (now.tm_mday / 365.25);
		double completionDate = dateComplete[0] + (dateComplete[1] / 12.0) + (dateComplete[2] / 365.25);
		//if difference between currentDate and completionDate is greater
		//than or equal to one day's portion of a year, reset
		if (frequency == "Daily" && (currentDate - completionDate >= (1 / 365.25))) {
			cout << "'" << name << "' has been reset!" << endl;
			setComplete(false);
			setDateCompleteFromFile("No");
			Pause();
		}
		//if difference between currentDate and completionDate is greater
		//than or equal to one week's portion of a year, reset
		if (frequency == "Weekly" && (currentDate - completionDate >= (1 / 52.1775))) {
			cout << "'" << name << "' has been reset!" << endl;
			setComplete(false);
			setDateCompleteFromFile("No");
			Pause();
		}
		//if difference between currentDate and completionDate is greater
		//than or equal to one month's portion of a year, reset
		if (frequency == "Monthly" && (currentDate - completionDate >= (1 / 12.0))) {
			cout << "'" << name << "' has been reset!" << endl;
			setComplete(false);
			setDateCompleteFromFile("No");
			Pause();
		}
	}
}