/**
	@file	getChar.cpp
	implementation file for getChar.h
	@author	Brady Helkenn
	@date	11/06/2014
*/
#include<iostream>
#include<string>
#include"getChar.h"
using namespace std;

char getChar() {
	char c = 0;
	bool isChar = false;
	while (!isChar) {
		string input;
		getline(cin, input);
		//verifies there's just a single char
		if (input.length() == 1) {
			c = input[0];
			isChar = true;
		}
		else {
			cout << "Invalid entry, please try again: ";
		}
	}
	return c;
}