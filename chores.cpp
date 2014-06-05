#include"chores.h"
#include<fstream>
using namespace std;

void chores::initChores() {
	fstream fs;
	string s;
	
	//Clears streams
	daily.str(s);
	weekly.str(s);
	monthly.str(s);

	fs.open("daily.txt");
	while(getline(fs, s)) {
		daily << s << endl;
	}
	fs.close();

	fs.open("weekly.txt");
	while(getline(fs, s)) {
		weekly << s << endl;
	}
	fs.close();

	fs.open("monthly.txt");
	while(getline(fs, s)) {
		monthly << s << endl;
	}
	fs.close();
}

void chores::mainMenu(char choice) {
	cout << "\nWhat would you like to do? " << endl;
	cout << "1. See outstanding chores" << endl;
	cout << "2. Enter a completed chore" << endl;
	cout << "3. Create a new chore" << endl;
	cout << "4. Permanently create a new chore" << endl;
	cout << "(V)iew notes" << endl;
	cout << "(C)reate notes for a chore" << endl;
	cout << "(R)eset program" << endl;
	cout << "(Q)uit this program :(" << endl;
	cin >> choice;

	string td = "daily.txt";
	string tw = "weekly.txt";
	string tm = "monthly.txt";
	string pd = "C:\\Users\\Brady\\Documents\\Applications Installed\\Productivity\\chores program\\backup files\\daily.txt";
	string pw = "C:\\Users\\Brady\\Documents\\Applications Installed\\Productivity\\chores program\\backup files\\weekly.txt";
	string pm = "C:\\Users\\Brady\\Documents\\Applications Installed\\Productivity\\chores program\\backup files\\monthly.txt";


	switch(choice) {
	case '1':
		displayChores();
		break;
	case '2':
		remChore(td, tw, tm);
		break;
	case '3':
		addChore(td, tw, tm);
		break;
	case '4':
		addChore(pd, pw, pm);
		break;
	case 'V':
		notesMenu();
		break;
	case 'v':
		notesMenu();
		break;
	case 'C':
		addNotes();
		break;
	case 'c':
		addNotes();
		break;
	case 'R':
		resetApp();
		break;
	case 'r':
		resetApp();
		break;
	case 'Q':
		exit(0);
	case 'q':
		exit(0);
	default:
		break;
	}
}

void chores::notesMenu() {
	int choice = 0;
	cout << "\nWhich chore would you like to see notes for? " << endl;
	
	for (int i = 0; i < number; i++) {
		cout << i + 1 << ". " << notes[i] << endl;
	}
	cin >> choice;
	//cout << "Need to run displayNotes() for: " << notes[choice - 1] << endl;

	cout << "\n\n\nNotes for '" << notes[choice - 1] << "':" << endl;
	cout << displayNotes(notes[choice - 1], choice) << endl;
}

string chores::displayNotes(string chore, int pos) {
	fstream fs;
	string filename = chore;
	filename.append(".txt");
	//cout << "filename = " << filename << endl;

	stringstream data;
	fs.open(filename);
	while (getline(fs, chore)) {
		data << chore << endl;
	}

	chore = data.str();

	return chore;
}

void chores::addNotes() {
	int choice = 0;
	cout << "\nWhich chore would you like to add notes to? " << endl;
	
	for (int i = 0; i < number; i++) {
		cout << i + 1 << ". " << notes[i] << endl;
	}
	cin >> choice;

	fstream fs;
	string filename = notes[choice - 1];
	filename.append(".txt");

	string note;
	cout << "Please enter your note: ";
	cin.ignore();
	getline(cin, note);
	
	fs.open(filename, ios::in|ios::out|ios::trunc);
	fs << note;
	fs.close();
}

void chores::displayChores() {
	cout << "\nOutstanding daily chores are: " << endl;
	cout << getDaily();

	cout << "\nOutstanding weekly chores are: " << endl;
	cout << getWeekly();

	cout << "\nOutstanding monthly chores are: " << endl;
	cout << getMonthly();
}

char chores::errorMenu() {
	cout << "Not found! What would you like to do?" << endl;
	cout << "1. Try inputting again" << endl;
	cout << "2. Go to main menu" << endl;
	char choice = '0';
	cin >> choice;
	return choice;
}

void chores::initNotes() {
	string s;

	all.str(s);
	all << daily.str() << weekly.str() << monthly.str();

	number = 0;

	int length = all.str().size();
	
	for (int i = 0; i < length; i++) {
		if (all.str()[i] == '\n') number++;
	}

	notes = new string[number];
	string line;

	int i = 0;
	while (getline(all, line)) {
		stringstream s(line);
		notes[i] = s.str();
		i++;
	}
}

void chores::addChore(string d, string w, string m) {
	char choice;
	typeOfChore(choice);

	string type, s;

	//second level menu
	switch(choice) {
	case '1':
		type = d;
		setString(s);
		appendTXT(type, s);
		if (d == "daily.txt") daily << s << endl;
		break;
	case '2':
		type = w;
		setString(s);
		appendTXT(type, s);
		if (w == "weekly.txt") weekly << s << endl;
		break;
	case '3':
		type = m;
		setString(s);
		appendTXT(type, s);
		if (m == "monthly.txt") monthly << s << endl;
		break;
	case '4':
		break;
	}
}

void chores::remChore(string d, string w, string m) {
	char choice;
	typeOfChore(choice);

	string type, sr, rem;
	
	//second level menu
	switch(choice) {
	case '1':
		type = d;
		sr = daily.str();
		setString(rem);
		rem.append(1, '\n');
		if (validateChore(sr, rem)) {remFromTXT(type, sr, rem);}
		daily.str(sr);
		break;
	case '2':
		type = w;
		sr = weekly.str();
		setString(rem);
		rem.append(1, '\n');
		if (validateChore(sr, rem)) {remFromTXT(type, sr, rem);}
		weekly.str(sr);
		break;
	case '3':
		type = m;
		sr = monthly.str();
		setString(rem);
		rem.append(1, '\n');
		if (validateChore(sr, rem)) {remFromTXT(type, sr, rem);}
		monthly.str(sr);
		break;
	case '4':
		return;
	}
}

void chores::typeOfChore(char& choice) {
	cout << "\nWhat type of chore would you like to enter? " << endl;
	cout << "1. Daily" << endl;
	cout << "2. Weekly" << endl;
	cout << "3. Monthly" << endl;
	cout << "4. Go back to main menu" << endl;
	cin >> choice;
}

void chores::appendTXT(string& s1, string& s2) {
	fstream fs;
	fs.open(s1, ios::in|ios::ate|ios::app);
	fs << s2 << endl;
	fs.close();
}

void chores::remFromTXT(string& s1, string& s2, string& rem) {
	fstream fs;

	fs.open(s1, ios::trunc|ios::out);
	s2.replace(s2.find(rem), rem.length(), "");
	fs << s2;
	fs.close();
}

void chores::setString(string& s) {
	cout << "Enter a chore: ";
	cin.ignore();
	getline(cin, s);
}

bool chores::validateChore(string& sr, string& rem) {
	if (sr.find(rem) != string::npos) return true;
	while (sr.find(rem) == string::npos) {
		switch(errorMenu()) {
		case '1':
			rem.erase();
			cout << "\nEnter a completed chore: ";
			cin >> rem;
			rem.append(1, '\n');

			if (sr.find(rem) != string::npos) return true;
			break;
		case '2':
			return false;
		default:
			break;
		}
	}
}

void chores::resetApp() {
	initChores();
	initNotes();
}