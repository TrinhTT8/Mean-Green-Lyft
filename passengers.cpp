//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu

#include "passengers.h"
#include "passenger.h"
#include <string>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <iterator>

using namespace std;

//Add passenger 
void Passengers::addPass() {
	string fname;
	string lname;
	int id;
	string payment;
	bool handicapped;
	double ratingrequired;
	bool pets;
	
	char response;
	int choice;
	//Create passenger object
	Passenger *temp;
	
	//Prompt user for name 
	cout << "Enter first name: ";
	getline(cin, fname);	
	cout << "Enter last name: ";
	getline(cin, lname);
	
	//Prompt user for payment reference 
	cout << "1 - Credit\t2 - Debit\t3 -  PayPal\n";
	cout << "Choose payment reference: ";
	cin >> choice;
	cin.ignore();
	// Set the payment method based on what the user pick
	if ( choice == 1 ) {
		payment = "credit";
	}
	else if ( choice == 2 ) {
		payment = "debit";
	}
	else {
		payment = "Paypal";
	}

	//Prompt user for handicap option
	cout << "Accessibility needs or handicaps? (Y/N) ";
	cin >> response;
	cin.ignore();
	
	// Set the handicapped value to either true or false
	if (response == 'Y' || response == 'y') { handicapped = true; }
	else { handicapped = false; }
	
	// Prompt user for pet option 
	cout << "Do you have pets? (Y/N): ";
	cin >> response;
	cin.ignore();
	
	if (response == 'Y' || response == 'y') { pets = true; }
	else { pets = false; }
	
	// Prompt user for default rating required 
	cout << "What's your required rating? ";
	cin >> ratingrequired;
	cin.ignore();
	
	// Generate a random user ID 
	srand(time(NULL));
	id = (rand() % 10000 + 10000);
	
	// Populate passenger object 
	temp = new Passenger(fname, lname, id, payment, handicapped, pets, ratingrequired);
	
	// Add object to collection 
	passList.push_back(temp);
}
	
// Store passengers
void Passengers::storePass () {
	ofstream fout;
	// Open file to write
	fout.open("passengers.dat");
	// Check if file opens
	if (!fout.is_open()) {
		cout << "Error opening file.\n";
	}
	fout << left << setw(20) << "First name" << left << setw(20) << "Last name" << left << setw(15) << "ID" << left << setw(15) << "Payment" << left << setw(15) << "Handicapped" << left << setw(15) << "Pets" << left << setw(20) << "Rating required" << endl;
	
	Passenger *temp;
	// Go through the list of passengers 
	for (auto it = passList.begin(); it != passList.end(); ++it) {
		temp = *it;
		// The file will write in the order of: name -> ID -> payment -> handicapped -> pets -> rating required
		fout << left << setw(20) << temp->getPassengerFname() << left << setw(20) << temp->getPassengerLname() << left << setw(15) << temp->getPassengerID() << left << setw(15) << temp->getPassengerPayment() << left << setw(15) << temp->getPassengerHandicapped() << left << setw(15) << temp->getPassengerPets() << left << setw(20) << temp->getPassengerRatingRequired() << endl;
	}
	fout.close();
}

//Load passengers
void Passengers::loadPass() {
	ifstream fin;
	string fname, lname;
	int id;
	string payment;
	bool handicapped;
	double ratingrequired;
	bool pets;
	
	string firstline;
	
	// Open the file to read
	fin.open("passengers.dat");
	getline(fin, firstline);
	
	// Read each category until the end of the line
	while (	fin >> fname >> lname >> id >> payment >> handicapped >> pets >> ratingrequired ) {
		// Add each readings to passList
		passList.push_back ( new Passenger(fname, lname, id, payment, handicapped, pets, ratingrequired));
	}
	fin.close();
}

// Deallocate memory of passenger list
void Passengers::clearPass() {
	for (auto it = passList.begin(); it != passList.end(); ++it) {
		delete *it;
	}
}

// Edit passenger
void Passengers::editPass() {
	string fname;
	string lname;
	string payment;
	bool handicapped;
	bool pets;
	double ratingrequired;
	
	int choice;
	int option;
	char response;
	bool passengerfound = false;

	do {
		// Ask the user if they want to search by name or ID
		cout << "What do you want to search by: 1 - Name\t 2 - ID\nEnter your choice: ";
		cin >> choice;
		cin.ignore();
		
		string searchFname;
		string searchLname;
		int searchid;
		
		// User choose to find the passenger by name
		if (choice == 1) {
			cout << "Enter passenger first name: ";
			getline(cin, searchFname);
			// Make all the letters in the name lower case
			for (int i = 0; i < searchFname.length(); ++i) {
				searchFname[i] = tolower(searchFname[i]);
			}
			cout << "Enter passenger last name: ";
			getline(cin, searchLname);
			for (int i = 0; i < searchLname.length(); ++i) {
				searchLname[i] = tolower(searchLname[i]);
			}
		}
		// User choose to find the passenger by ID
		else {
			cout << "Enter passenger ID: ";
			cin >> searchid;
		}  
		
		string storeFname;
		string storeLname;
		// Goes through each passenger in the passenger list
		for (auto it = passList.begin(); it != passList.end(); ++it) {
			Passenger *pass = *it;
			// Get the passenger first name and last name in the saved data
			storeFname = pass->getPassengerFname();
			storeLname = pass->getPassengerLname();
			
			// Switch all the letters in the first name and last name to lower case for comparison
			for (int i = 0; i < storeFname.length(); ++i) {
				storeFname[i] = tolower(storeFname[i]);
			}
			for (int i = 0; i < storeLname.length(); ++i) {
				storeLname[i] = tolower(storeLname[i]);
			}
			
			// If the user's input matches either the name or the ID stored in the system
			if ( (storeFname == searchFname) && (storeLname == searchLname ) || ( pass->getPassengerID() == searchid) )
			{
				// Ask what category needs to be edit
				cout << " 1 - Name\n 2 - Payment preference\n 3 - Handicapped\n 4 - Pets\n 5 - Rating required\n";
				cout << "What do you want to edit? ";
				cin >> option;
				cin.ignore();
				
				switch(option) {
					case 1:
					// Edit name
					cout << "Enter your new first name: ";
					getline(cin, fname);
					cout << "Enter your new last name: ";
					getline(cin, lname);
					
					// Update the new name
					pass->setPassengerFname(fname);
					pass->setPassengerLname(lname);
					break;
					
					case 2:
					// Edit payment preference
					cout << "1 - Credit\t2 - Debit\t3 -  PayPal\n";
					cout << "Choose your new payment reference: ";
					cin >> choice;
					cin.ignore();
					if ( choice == 1 ) {
						payment = "credit";
					}
					else if ( choice == 2 ) {
						payment = "debit";
					}
					else {
						payment = "paypal";
					}
					// Update the new payment preference
					pass->setPassengerPayment(payment);
					break;
					
					case 3:
					// Edit handicapped option
					cout << "Accessibility needs or handicaps? (Y/N) ";
					cin >> response;
					cin.ignore();
					// Set true or false for the boolean
					if (response == 'Y' || response == 'y') { handicapped = true; }
					else { handicapped = false; }
					// Update the new handicap option
					pass->setPassengerHandicapped(handicapped);
					break;
					
					case 4:
					// Edit pets option
					cout << "Do you have pets? (Y/N): ";
					cin >> response;
					cin.ignore();
					// Set true or false for the boolean	
					if (response == 'Y' || response == 'y') { pets = true; }
					else { pets = false; }	
					// Update the new pet option
					pass->setPassengerPets(pets);
					break;
					
					case 5:
					// Edit default rating required
					cout << "What's your new required rating? ";
					cin >> ratingrequired;
					cin.ignore();
					// Update the new rating required
					pass->setPassengerRatingRequired(ratingrequired);
					break;
				}
				passengerfound = true;
				// Print out the updated information
				cout << "\n*Passenger updated information*\n";
				cout << "Name: " << pass->getPassengerFname() << " " << pass->getPassengerLname() << endl << "ID: " << pass->getPassengerID() << endl << "Payment: " << pass->getPassengerPayment() << endl << "Default rating required: " << pass->getPassengerRatingRequired() << endl;
					
				if(pass->getPassengerHandicapped() == 1) {
					cout << "Handicapped: Yes\n";
				}
				else {
					cout << "Handicapped: No\n";
				}
			
				if(pass->getPassengerPets() == 1) {
					cout << "Pets: Yes\n";
				}
				else {
					cout << "Pets: No\n";
				}		
			}
		}
			// If the user's input does not match either the name or the ID, display an error message
			if (!passengerfound) { cout << "Passenger not found.\n";  }
	} while (!passengerfound);
}
			
//Delete passenger 
void Passengers::deletePass() {
	
	string searchFname;
	string searchLname;
	string storeFname;
	string storeLname;
	bool passengerfound = false;
	int searchid;
	int choice;
	
	//Let user search by name or ID
	cout << "What do you want to search by: 1 - Name\t 2 - ID\nEnter your choice: ";
	cin >> choice;
	cin.ignore();
	

	//User choose to find the passenger by name
	if (choice == 1) {
		cout << "Enter passenger first name: ";
		getline(cin, searchFname);
		for (int i = 0; i < searchFname.length(); ++i) {
			searchFname[i] = tolower(searchFname[i]);
		}
		cout << "Enter passenger last name: ";
		getline(cin, searchLname);
		for (int i = 0; i < searchLname.length(); ++i) {
			searchLname[i] = tolower(searchLname[i]);
		}
	}
	//User choose to find the passenger by ID
	else {
		cout << "Enter passenger ID: ";
		cin >> searchid;
	} 

	for (auto it = passList.begin(); it != passList.end(); ++it) {
		Passenger *pass = *it;
		// Check if passenger exists
		storeFname = pass->getPassengerFname();
		storeLname = pass->getPassengerLname();
		// Switch all the letters in the name to lower case for comparison
		for (int i = 0; i < storeFname.length(); ++i) {
			storeFname[i] = tolower(storeFname[i]);
		}
		
		for (int i = 0; i < storeLname.length(); ++i) {
			storeLname[i] = tolower(storeLname[i]);
		}
		
		// If the user's input matches either the name or the ID 
		if ( (storeFname == searchFname) && (storeLname == searchLname ) || ( pass->getPassengerID() == searchid) )
		{
		// Delete the passenger information from the collection (name, ID, etc.) if the ID exists 
			passList.erase(it);
			passengerfound = true;
			cout << "\nPassenger successful deleted.\n";
			return;
		}
	}
	//Return error message if the ID doesn’t exist  
	if ( !passengerfound ) { cout << "\nPassenger not found.\n"; }
}
 
// Find passenger based on appropriate criteria 
Passenger* Passengers::findPass() {
	string searchFname;
	string searchLname;
	string storeFname;
	string storeLname;
	string searchpayment;
	int searchid;
	bool searchhandicapped;
	bool searchpets;
	double searchrating;
	
	bool passengerfound = false;
	char choice;
	
	Passenger *pass = nullptr;
	// Display a search menu to ask what the user is searching for 
	cout << "-----Criteria to search for-----\n";
	cout << " N - Name\n I - ID\n A - Payment preference \n H - Handicapped\n P - Pets\n R - Default rating required\n";
	cout << "What are you looking for? ";
	cin >> choice;
	choice = toupper(choice);
	cin.ignore();

	switch(choice) {
		// User want to search based on name
		case 'N':
			cout << "Enter passenger first name: ";
			getline(cin, searchFname);
			for (int i = 0; i < searchFname.length(); ++i) {
				searchFname[i] = tolower(searchFname[i]);
			}
			cout << "Enter passenger last name: ";
			getline(cin, searchLname);
			for (int i = 0; i < searchLname.length(); ++i) {
				searchLname[i] = tolower(searchLname[i]);
			}
			for(auto it = passList.begin(); it != passList.end(); it++) {
				storeFname = (*it)->getPassengerFname();
				storeLname = (*it)->getPassengerLname();
		
				for (int i = 0; i < storeFname.length(); ++i) {
					storeFname[i] = tolower(storeFname[i]);
				}
		
				for (int i = 0; i < storeLname.length(); ++i) {
					storeLname[i] = tolower(storeLname[i]);
				}	
				// Print passenger information if the passenger is found
				if ((storeFname == searchFname) && (storeLname== searchLname)) {
						(*it)->printPassenger();
						passengerfound = true;
					}			
			}
				if (!passengerfound) { cout << "No matching passengers found.\n"; }
			break;
		
		// User want to search based on ID
		case 'I':
			cout << "Enter passenger ID: ";
			cin >> searchid;
			cin.ignore();
			// Print passenger information if the ID is found
			for(auto it = passList.begin(); it != passList.end(); it++) {
				if ((*it)->getPassengerID() == searchid) {
					(*it)->printPassenger();
					passengerfound = true;
				}
			}
			if (!passengerfound) { cout << "No matching passengers found.\n"; }
			break;
		
		// User want to search based on payment preference
		case 'A':
			cout << "Enter passenger payment preference (credit/debit/paypal) : ";
			getline(cin, searchpayment);
			// Switch all letters to lowercase before comparing
			for (int i = 0; i < searchpayment.length(); i++) {
				searchpayment[i] = tolower(searchpayment[i]);
			}
			for(auto it = passList.begin(); it != passList.end(); it++) {
				if ((*it)->getPassengerPayment() == searchpayment) {
					(*it)->printPassenger();
					passengerfound = true;
				}
			}
			if (!passengerfound) { cout << "No matching passengers found.\n"; }
			break;
			
		// User want to search based on handicapped
		case 'H':
			cout << "Accessibility needs or handicaps? (Y/N) ";
			cin >> choice;
			
			if ( choice == 'y' || choice == 'Y' ) { searchhandicapped = true; }
			else { searchhandicapped = false; }
			
			for(auto it = passList.begin(); it != passList.end(); it++) {
				if ((*it)->getPassengerHandicapped() == searchhandicapped) {
					(*it)->printPassenger();
					passengerfound = true;
				}
			}
			if (!passengerfound) { cout << "No matching passengers found.\n"; }
			break;
		
		//  User want to search based on pets
		case 'P':
			cout << "Passengers have pets? (Y/N) ";
			cin >> choice;
			
			if ( choice == 'y' || choice == 'Y' ) { searchpets = true; }
			else { searchpets = false; }
			
			for(auto it = passList.begin(); it != passList.end(); it++) {
				if ((*it)->getPassengerPets() == searchpets) {
					(*it)->printPassenger();
					passengerfound = true;
				}
			}
			if (!passengerfound) { cout << "No matching passengers found.\n"; }
			break;
		
		//User want to search based on default rating required
		case 'R':
			cout << "What is the minimum rating you are looking for? ";
			cin >> searchrating;
			cin.ignore();
			
			for(auto it = passList.begin(); it != passList.end(); it++) {
				if ((*it)->getPassengerRatingRequired() >= searchrating) {
					(*it)->printPassenger();
					passengerfound = true;
				}
			}
			if (!passengerfound) { cout << "No matching passengers found.\n"; }
			break;
		
		default: cout << "Invalid choice\n"; break;
			
	}
	return pass;
} 

//Print passengers 
void Passengers::printAllPass() {
	cout << "Number of passengers: " << passList.size() << endl;
	cout << left << setw(15) << "First name" << left << setw(15) << "Last name" << left << setw(10) << "ID" << left << setw(15) << "Payment" << left << setw(20) << "Handicapped" << left << setw(15) << "Pets" << left << setw(15) << "Rating required" << endl;
	
	//Iterate through each passenger in Passenger list 
	for (auto it = passList.begin(); it != passList.end(); ++it) {
		
		//Access the passenger object from the iterator
		Passenger *pass = *it;
	
		//Print out each passenger’s data (name, ID, etc.) 
		cout << left << setw(15) << pass->getPassengerFname() << left << setw(15) << pass->getPassengerLname() << left << setw(10) << pass->getPassengerID() << left << setw(15) << pass->getPassengerPayment();  
		
		if(pass->getPassengerHandicapped() == 1) {
			cout << left << setw(20) << "Yes";
		}
		else {
			cout << left << setw(20) << "No";
		}
		
		if(pass->getPassengerPets() == 1) {
			cout << left << setw(15) << "Yes";
		}
		else {
			cout << left << setw(15) << "No";
		}
		
		cout << left << setw(15) << pass->getPassengerRatingRequired() << endl;
	}
	cout << endl;
}

// Get the list of passengers
vector<Passenger*>& Passengers::getPassList() {
	return passList;
}

