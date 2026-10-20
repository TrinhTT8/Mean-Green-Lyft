//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu

#include "passenger.h"
#include "utils.h"
#include <iomanip>

// Constructor for the Passenger class
Passenger::Passenger (const string& Pfname, const string& Plname, int Pid, const string& Ppay, bool Phandicapped, bool Ppets, double Prating)
	// Initialize passenger variables with provided values
	: PassFname(Pfname), PassLname(Plname), PassID(Pid), PassPayment(Ppay),
	  PassHandicapped(Phandicapped), PassRatingRequired(Prating), PassPets(Ppets) {}

// Print the column titles for passenger information
void Passenger::printHeader() {
	cout << left << setw(15) << "First name" << setw(15) << "Last name" << setw(10) << "ID" << setw(15) << "Payment" << setw(20) << "Handicapped" << setw(15) << "Pets" << setw(15) << "Rating required" << endl;
}

// Print one row of passenger information
void Passenger::printRow() const {
	cout << left << setw(15) << PassFname << setw(15) << PassLname << setw(10) << PassID << setw(15) << PassPayment
	     << setw(20) << yesNo(PassHandicapped) << setw(15) << yesNo(PassPets) << setw(15) << PassRatingRequired << endl;
}

// Print passenger information
void Passenger::printPassenger() const {
	printHeader();
	printRow();
	cout << endl;
}
