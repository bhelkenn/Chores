#include<time.h>
#include"chores.h"
using namespace std;

int main() {
	//Introduction
	cout << "Welcome to the chores program!" << endl;

	//Initialize and populate class
	chores chore;
	chore.resetApp();
	chore.displayChores();

	char choice = '0';
	do {chore.mainMenu(choice);} while (choice != 'q' || choice != 'Q');
}

//string timestamp() {
//	// Current date/time based on current system 
//	time_t now = time(0); 
// 
//	// Convert now to tm struct for local timezone 
//	tm*	localtm = localtime(&now); 
//
//	//Debugging
//	//cout << "The local date and time is: " << asctime(localtm) << endl;
//	
//	string datetime = asctime(localtm);
//
//	return datetime;
//}