//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu

#include "utils.h"

#include <iostream>
#include <limits>
#include <cctype>

using namespace std;

// Discard everything left on the current input line
static void skipLine() {
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Stop asking once there is no more input, so the program cannot loop forever
static void checkInputEnded() {
	if (cin.eof()) { throw InputEnded(); }
}

// Return a lower case copy of the string
string toLower(string s) {
	for (char& c : s) {
		c = tolower(static_cast<unsigned char>(c));
	}
	return s;
}

// Compare two strings without caring about upper/lower case
bool equalsIgnoreCase(const string& a, const string& b) {
	if (a.size() != b.size()) { return false; }
	for (size_t i = 0; i < a.size(); ++i) {
		if (tolower(static_cast<unsigned char>(a[i])) != tolower(static_cast<unsigned char>(b[i]))) { return false; }
	}
	return true;
}

const char* yesNo(bool value) {
	return value ? "Yes" : "No";
}

// Read an integer, asking again if the user types something that is not a number
int askInt(const string& prompt) {
	int value;
	cout << prompt;
	while (!(cin >> value)) {
		checkInputEnded();
		cin.clear();
		skipLine();
		cout << "Please enter a number: ";
	}
	skipLine();
	return value;
}

// Read a decimal number, asking again if the user types something that is not a number
double askDouble(const string& prompt) {
	double value;
	cout << prompt;
	while (!(cin >> value)) {
		checkInputEnded();
		cin.clear();
		skipLine();
		cout << "Please enter a number: ";
	}
	skipLine();
	return value;
}

char askChar(const string& prompt) {
	char c;
	cout << prompt;
	cin >> c;
	checkInputEnded();
	skipLine();
	return toupper(static_cast<unsigned char>(c));
}

bool askYesNo(const string& prompt) {
	return askChar(prompt) == 'Y';
}

string askLine(const string& prompt) {
	string line;
	cout << prompt;
	if (!getline(cin, line)) { checkInputEnded(); }
	return line;
}

string chooseVehicleType(const string& prompt) {
	static const string types[] = { "convertible", "coupe", "compact", "crossover", "electric", "hatchback",
	                                "hybrid", "minivan", "sedan", "suv", "truck", "limo" };
	const int numTypes = sizeof(types) / sizeof(types[0]);

	cout << "1 - Convertible\n2 - Coupe\n3 - Compact\n4 - Crossover\n5 - Electric\n6 - Hatchback\n7 - Hybrid\n8 - Minivan\n9 - Sedan\n10 - SUV\n11 - Truck\n12 - Limo\n";
	int choice = askInt(prompt);
	// Keep asking until the choice is on the menu
	while (choice < 1 || choice > numTypes) {
		cout << "Invalid choice\n";
		choice = askInt(prompt);
	}
	return types[choice - 1];
}

bool SearchKey::matches(const string& otherFname, const string& otherLname, int otherId) const {
	if (byName) {
		return equalsIgnoreCase(fname, otherFname) && equalsIgnoreCase(lname, otherLname);
	}
	return id == otherId;
}

SearchKey askSearchKey(const string& who) {
	SearchKey key;
	key.byName = (askInt("What do you want to search by: 1 - Name\t 2 - ID\nEnter your choice: ") == 1);
	key.id = -1;

	// User choose to find by name
	if (key.byName) {
		key.fname = toLower(askLine("Enter " + who + " first name: "));
		key.lname = toLower(askLine("Enter " + who + " last name: "));
	}
	// User choose to find by ID
	else {
		key.id = askInt("Enter " + who + " ID: ");
	}
	return key;
}
