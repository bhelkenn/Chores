/**
	@file	getInt.cpp
	implementation file for getInt.h
	@author	Brady Helkenn
	@date	11/06/2014
*/
#include<iostream>
#include<sstream>
#include<string>
#include"getInt.h"
using namespace std;

int getInt() {
	int num = 0;
	bool isInt = false;
	while (!isInt) {
		string input;
		getline(cin, input);
		//convert from string to number safely.
		stringstream ss(input);
		if (ss >> num) {
			isInt = true;
		}
		else {
			cout << "Invalid entry, please try again: ";
		}
	}
	return num;
}