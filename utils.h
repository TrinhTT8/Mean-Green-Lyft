//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu

#ifndef UTILS_H
#define UTILS_H

#include <string>

using namespace std;

// String helpers
string toLower(string s);
bool equalsIgnoreCase(const string& a, const string& b);
const char* yesNo(bool value);

// Thrown by the input helpers when there is no more input (end of file / Ctrl+D)
struct InputEnded {};

// Input helpers: each prints the prompt, reads a value and discards the rest of the line
int askInt(const string& prompt);
double askDouble(const string& prompt);
char askChar(const string& prompt);			// Returns the character in upper case
bool askYesNo(const string& prompt);		// True only for 'Y' or 'y'
string askLine(const string& prompt);

// Shows the vehicle type menu and returns the chosen type
string chooseVehicleType(const string& prompt);

// Search key used to find a passenger or driver by name or by ID
struct SearchKey {
	bool byName;
	string fname;		// Stored in lower case
	string lname;		// Stored in lower case
	int id;

	bool matches(const string& otherFname, const string& otherLname, int otherId) const;
};

// Asks "1 - Name / 2 - ID" and reads the matching key. who is "driver" or "passenger"
SearchKey askSearchKey(const string& who);

#endif
