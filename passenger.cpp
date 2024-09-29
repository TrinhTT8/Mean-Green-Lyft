//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu

#include "passenger.h"
#include <iomanip>

// Constructor for the Passenger class
Passenger::Passenger (string Pfname, string Plname, int Pid, string Ppay, bool Phandicapped, bool Ppets, double Prating) {
	// Initialize passenger variables with provided values
	PassFname = Pfname;
	PassLname = Plname;
	PassID = Pid;
	PassPayment = Ppay;
	PassRatingRequired = Prating;
	PassHandicapped = Phandicapped;
	PassPets = Ppets;
}

// Update passenger's first name
void Passenger::setPassengerFname(string Pfname) {
	PassFname = Pfname;
}

// Update passenger's last name
void Passenger::setPassengerLname(string Plname) {
	PassLname = Plname;
}

// Update passenger's id
void Passenger::setPassengerID (int Pid) {
	PassID = Pid;
}

// Update passenger's payment method
void Passenger::setPassengerPayment (string Ppay) {
	PassPayment = Ppay;
}

// Update whether passenger is handicapped
void Passenger::setPassengerHandicapped (bool Phandicapped) {
	PassHandicapped = Phandicapped;
}

// Update passenger's required rating
void Passenger::setPassengerRatingRequired(double Prating) {
	PassRatingRequired = Prating;
}

// Update whether passenger has pets
void Passenger::setPassengerPets(bool Ppets) {
	PassPets = Ppets;
}

// Print passenger information
void Passenger::printPassenger() {
	cout << left << setw(15) << "First name" << left << setw(15) << "Last name" << left << setw(10) << "ID" << left << setw(15) << "Payment" << left << setw(20) << "Handicapped" << left << setw(15) << "Pets" << left << setw(15) << "Rating required" << endl;
	cout << left << setw(15) << PassFname << left << setw(15) << PassLname << left << setw(10) << PassID << left << setw(15) << PassPayment;  
		// Display yes if bool value is 0 or else display no
		if(PassHandicapped == 1) {
			cout << left << setw(20) << "Yes";
		}
		else {
			cout << left << setw(20) << "No";
		}
		
		if(PassPets == 1) {
			cout << left << setw(15) << "Yes";
		}
		else {
			cout << left << setw(15) << "No";
		}
		cout << left << setw(15) << PassRatingRequired << endl << endl;
}
		
