//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu

#include "passengers.h"
#include "passenger.h"
#include "utils.h"
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

// Show the payment menu and return the chosen payment method
static string choosePayment(const string& prompt, const string& paypalName) {
	cout << "1 - Credit\t2 - Debit\t3 -  PayPal\n";
	int choice = askInt(prompt);
	if ( choice == 1 ) { return "credit"; }
	if ( choice == 2 ) { return "debit"; }
	return paypalName;
}

// Print every passenger that passes the test. Returns true if at least one was printed
template <typename Test>
static bool printMatching(const vector<Passenger*>& passList, Test test) {
	bool passengerfound = false;
	for (const Passenger* pass : passList) {
		if (test(pass)) {
			pass->printPassenger();
			passengerfound = true;
		}
	}
	return passengerfound;
}

//Add passenger
void Passengers::addPass() {
	//Prompt user for name
	string fname = askLine("Enter first name: ");
	string lname = askLine("Enter last name: ");

	//Prompt user for payment reference
	string payment = choosePayment("Choose payment reference: ", "Paypal");

	//Prompt user for handicap and pet options
	bool handicapped = askYesNo("Accessibility needs or handicaps? (Y/N) ");
	bool pets = askYesNo("Do you have pets? (Y/N): ");

	// Prompt user for default rating required
	double ratingrequired = askDouble("What's your required rating? ");

	// Generate a random user ID
	int id = (rand() % 10000 + 10000);

	// Populate passenger object and add it to collection
	passList.push_back(new Passenger(fname, lname, id, payment, handicapped, pets, ratingrequired));
}

// Store passengers
void Passengers::storePass () const {
	// Open file to write
	ofstream fout("passengers.dat");
	// Check if file opens
	if (!fout.is_open()) {
		cout << "Error opening file.\n";
		return;
	}
	fout << left << setw(20) << "First name" << setw(20) << "Last name" << setw(15) << "ID" << setw(15) << "Payment" << setw(15) << "Handicapped" << setw(15) << "Pets" << setw(20) << "Rating required" << endl;

	// Go through the list of passengers
	for (const Passenger* temp : passList) {
		// The file will write in the order of: name -> ID -> payment -> handicapped -> pets -> rating required
		fout << left << setw(20) << temp->getPassengerFname() << setw(20) << temp->getPassengerLname() << setw(15) << temp->getPassengerID() << setw(15) << temp->getPassengerPayment() << setw(15) << temp->getPassengerHandicapped() << setw(15) << temp->getPassengerPets() << setw(20) << temp->getPassengerRatingRequired() << endl;
	}
}

//Load passengers
void Passengers::loadPass() {
	string fname, lname, payment, firstline;
	int id;
	bool handicapped, pets;
	double ratingrequired;

	// Open the file to read and skip the column titles
	ifstream fin("passengers.dat");
	getline(fin, firstline);

	// Read each category until the end of the line
	while (	fin >> fname >> lname >> id >> payment >> handicapped >> pets >> ratingrequired ) {
		// Add each readings to passList
		passList.push_back ( new Passenger(fname, lname, id, payment, handicapped, pets, ratingrequired));
	}
}

// Deallocate memory of passenger list
void Passengers::clearPass() {
	for (Passenger* pass : passList) {
		delete pass;
	}
	passList.clear();
}

// Edit passenger
void Passengers::editPass() {
	bool passengerfound = false;

	do {
		// Ask the user if they want to search by name or ID
		SearchKey key = askSearchKey("passenger");

		// Goes through each passenger in the passenger list
		for (Passenger* pass : passList) {
			// If the user's input matches either the name or the ID stored in the system
			if (!key.matches(pass->getPassengerFname(), pass->getPassengerLname(), pass->getPassengerID())) { continue; }

			// Ask what category needs to be edit
			cout << " 1 - Name\n 2 - Payment preference\n 3 - Handicapped\n 4 - Pets\n 5 - Rating required\n";
			int option = askInt("What do you want to edit? ");

			switch(option) {
				case 1: {
					// Edit name
					string fname = askLine("Enter your new first name: ");
					string lname = askLine("Enter your new last name: ");
					pass->setPassengerFname(fname);
					pass->setPassengerLname(lname);
					break;
				}
				case 2:
					// Edit payment preference
					pass->setPassengerPayment(choosePayment("Choose your new payment reference: ", "paypal"));
					break;
				case 3:
					// Edit handicapped option
					pass->setPassengerHandicapped(askYesNo("Accessibility needs or handicaps? (Y/N) "));
					break;
				case 4:
					// Edit pets option
					pass->setPassengerPets(askYesNo("Do you have pets? (Y/N): "));
					break;
				case 5:
					// Edit default rating required
					pass->setPassengerRatingRequired(askDouble("What's your new required rating? "));
					break;
			}
			passengerfound = true;
			// Print out the updated information
			cout << "\n*Passenger updated information*\n";
			cout << "Name: " << pass->getPassengerFname() << " " << pass->getPassengerLname() << endl << "ID: " << pass->getPassengerID() << endl << "Payment: " << pass->getPassengerPayment() << endl << "Default rating required: " << pass->getPassengerRatingRequired() << endl;
			cout << "Handicapped: " << yesNo(pass->getPassengerHandicapped()) << "\n";
			cout << "Pets: " << yesNo(pass->getPassengerPets()) << "\n";
		}
		// If the user's input does not match either the name or the ID, display an error message
		if (!passengerfound) { cout << "Passenger not found.\n";  }
	} while (!passengerfound);
}

//Delete passenger
void Passengers::deletePass() {
	//Let user search by name or ID
	SearchKey key = askSearchKey("passenger");

	for (auto it = passList.begin(); it != passList.end(); ++it) {
		Passenger *pass = *it;
		// If the user's input matches either the name or the ID
		if (key.matches(pass->getPassengerFname(), pass->getPassengerLname(), pass->getPassengerID())) {
			// Delete the passenger information from the collection (name, ID, etc.) if the ID exists
			delete pass;
			passList.erase(it);
			cout << "\nPassenger successful deleted.\n";
			return;
		}
	}
	//Return error message if the ID doesn’t exist
	cout << "\nPassenger not found.\n";
}

// Find passenger based on appropriate criteria
Passenger* Passengers::findPass() const {
	bool passengerfound = false;

	// Display a search menu to ask what the user is searching for
	cout << "-----Criteria to search for-----\n";
	cout << " N - Name\n I - ID\n A - Payment preference \n H - Handicapped\n P - Pets\n R - Default rating required\n";
	char choice = askChar("What are you looking for? ");

	switch(choice) {
		// User want to search based on name
		case 'N': {
			string searchFname = askLine("Enter passenger first name: ");
			string searchLname = askLine("Enter passenger last name: ");
			passengerfound = printMatching(passList, [&](const Passenger* p) {
				return equalsIgnoreCase(p->getPassengerFname(), searchFname) && equalsIgnoreCase(p->getPassengerLname(), searchLname);
			});
			break;
		}

		// User want to search based on ID
		case 'I': {
			int searchid = askInt("Enter passenger ID: ");
			passengerfound = printMatching(passList, [&](const Passenger* p) { return p->getPassengerID() == searchid; });
			break;
		}

		// User want to search based on payment preference
		case 'A': {
			string searchpayment = askLine("Enter passenger payment preference (credit/debit/paypal) : ");
			passengerfound = printMatching(passList, [&](const Passenger* p) { return equalsIgnoreCase(p->getPassengerPayment(), searchpayment); });
			break;
		}

		// User want to search based on handicapped
		case 'H': {
			bool searchhandicapped = askYesNo("Accessibility needs or handicaps? (Y/N) ");
			passengerfound = printMatching(passList, [&](const Passenger* p) { return p->getPassengerHandicapped() == searchhandicapped; });
			break;
		}

		//  User want to search based on pets
		case 'P': {
			bool searchpets = askYesNo("Passengers have pets? (Y/N) ");
			passengerfound = printMatching(passList, [&](const Passenger* p) { return p->getPassengerPets() == searchpets; });
			break;
		}

		//User want to search based on default rating required
		case 'R': {
			double searchrating = askDouble("What is the minimum rating you are looking for? ");
			passengerfound = printMatching(passList, [&](const Passenger* p) { return p->getPassengerRatingRequired() >= searchrating; });
			break;
		}

		default:
			cout << "Invalid choice\n";
			return nullptr;
	}
	if (!passengerfound) { cout << "No matching passengers found.\n"; }
	return nullptr;
}

//Print passengers
void Passengers::printAllPass() const {
	cout << "Number of passengers: " << passList.size() << endl;
	Passenger::printHeader();

	//Print out each passenger’s data (name, ID, etc.)
	for (const Passenger* pass : passList) {
		pass->printRow();
	}
	cout << endl;
}

// Get the list of passengers
vector<Passenger*>& Passengers::getPassList() {
	return passList;
}
