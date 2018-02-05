/**
	@file	Pause.cpp
	Implementation file for Pause.h
	@author	Brady Helkenn
	@date	11/06/2014
*/
#include<iostream>
#include"Pause.h"
using namespace std;

void Pause() {
	cout << "Press ENTER to continue...";
	char c[15];
	cin.getline(c, 15);
}