//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu

#include "driver.h"
#include <iomanip>

// Constructor for the Driver class
Driver::Driver(string Dfname, string Dlname, string Dvehicletype, string Dnotes, int Did, int Dvehiclecap, bool Dhandicapped, bool Dpets, bool Davailable, double Drating) {		
	// Initialize driver variables with provided values		
		DriverFname = Dfname;
		DriverLname = Dlname;
		DriverVehicleType = Dvehicletype;
		DriverNotes = Dnotes;
		DriverId = Did;
		DriverVehicleCapacity = Dvehiclecap;
		DriverRating = Drating;
		DriverHandicapped = Dhandicapped;
		DriverAvailability = Davailable;
		DriverPets = Dpets;
}
// Update driver's first name	
void Driver::setDriverFName(string Dfname) { DriverFname = Dfname; }

// Update driver's last name
void Driver::setDriverLName(string Dlname) { DriverLname = Dlname; }

// Update driver's ID
void Driver::setDriverID (int Did) { DriverId = Did; }

// Update driver's vehicle type
void Driver::setDriverVehicleType(string Dvehicletype) { DriverVehicleType = Dvehicletype; }

// Update driver's vehicle capacity
void Driver::setDriverVehicleCapacity(int Dvehiclecap) { DriverVehicleCapacity = Dvehiclecap; }

// Update driver's rating
void Driver::setDriverRating(double Drating) { DriverRating = Drating; }

// Update driver's handicap policy
void Driver::setDriverHandicapped (bool Dhandicapped) { DriverHandicapped = Dhandicapped; }

// Update driver's pet policy
void Driver::setDriverPets(bool Dpets) { DriverPets = Dpets; }

// Update driver's availability 
void Driver::setDriverAvailability (bool Davailable) { DriverAvailability = Davailable; }

// Update driver's notes
void Driver::setDriverNotes (string Dnotes) { DriverNotes = Dnotes; }

// Check the criteria of specific driver. The function returns true or false
bool Driver::CriteriaMatch(int partysize, bool pet, bool handicap, double requiredrating) {
	// Check if the driver has enough seats 
	if (partysize > DriverVehicleCapacity) { return false; }
    // Check if the driver allows pets
    if (pet == true && !DriverPets) { return false; }
    // Check if the driver's vehicle is handicap-accessible
    if (handicap == true && !DriverHandicapped) { return false; }
    // Check if the driver's rating meets the required rating
    if (requiredrating > DriverRating && DriverRating != 0) { return false; }
    // If all criteria are met, return true
    return true;
}	

// Print driver's information
void Driver::printDriver () {
	cout << left << setw(13) << "First name" << left << setw(13) << "Last name" << left << setw(8) << "ID" << left << setw(15) << "Vehicle type" << left << setw(7) << "Seats" << left << setw(20) << "Handicapped option" << left << setw(15) << "Pet option" << left << setw(10) << "Rating" << setw(15) << "Available" << endl;	
	cout << left << setw(13) << DriverFname << left << setw(13) << DriverLname << left << setw(8) << DriverId << left << setw(15) << DriverVehicleType << left << setw(7) << DriverVehicleCapacity;
		if(DriverHandicapped == 1) {
			cout << left << setw(20) << "Yes";
		}
		else {
			cout << left << setw(20) << "No";
		}
		
		if(DriverPets == 1) {
			cout << left << setw(15) << "Yes";
		}
		else {
			cout << left << setw(15) << "No";
		}
		cout << left << setw(10) << DriverRating;
		if(DriverAvailability == 1) {
			cout << "Yes\n";
		}
		else {
			cout << "No\n";
		}
		cout << "Notes: " << DriverNotes << endl;
}

void Driver::editDriver() {
	string fname;
	string lname;
	string vehicletype;
	string notes;
	string carRestrict;
	string carAmen;
	int vehiclecapacity;
	bool handicapped;
	bool pets;
	
	int choice;
	int option;
	char response;
	
	// Ask what category needs to be edit
		cout << " 1 - Name\n 2 - Vehicle Type\n 3 - Vehicle Capacity\n 4 - Handicapped option\n 5 - Pets option\n 6 - Notes\n 7 - Editing driver features\n";
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
				
			// Update new name
			setDriverFName(fname);
			setDriverLName(lname);
			break;
				
			case 2:
			// Edit vehicle type
			cout << "1 - Convertible\n2 - Coupe\n3 - Compact\n4 - Crossover\n5 - Electric\n6 - Hatchback\n7 - Hybrid\n8 - Minivan\n9 - Sedan\n10 - SUV\n11 - Truck\n12 - Limo\n";
			cout << "Choose your new vehicle type: ";
			cin >> choice;
			cin.ignore();
				switch (choice) {
					case 1: vehicletype = "convertible"; break;
					case 2: vehicletype = "coupe"; break;
					case 3: vehicletype = "compact"; break;
					case 4: vehicletype = "crossover"; break;
					case 5: vehicletype = "electric"; break;
					case 6: vehicletype = "hatchback"; break;
					case 7: vehicletype = "hybrid"; break;
					case 8: vehicletype = "minivan"; break;
					case 9: vehicletype = "sedan"; break;
					case 10: vehicletype = "suv"; break;
					case 11: vehicletype = "truck"; break;
					case 12: vehicletype = "limo"; break;
					default: cout << "Invalid choice"; break;
				}
				// Update new driver vehicle type
			setDriverVehicleType(vehicletype);
			break;
				
			case 3:
			// Edit vehicle capacity
			cout << "Enter new vehicle capacity: ";
			cin >> vehiclecapacity;
			cin.ignore();
			// Update new driver vehicle capacity
			setDriverVehicleCapacity(vehiclecapacity);
			break;
				
			case 4:
			// Edit handicapped option
			cout << "Handicap accessiblity options (Y/N): ";
			cin >> response;
			cin.ignore();
	
			if (response == 'Y' || response == 'y') { handicapped = true; }
			else { handicapped = false; }
			// Update new driver handicap option
			setDriverHandicapped(handicapped);
			break;
				
			case 5:
			// Edit pets option
			cout << "Pets option? (Y/N): ";
			cin >> response;
			cin.ignore();
				if (response == 'Y' || response == 'y') { pets = true; }
				else { pets = false; }	
			// Update new driver pet policy
			setDriverPets(pets);
			break;
				
			case 6:
			//Edit driver notes
			cout << "Other informations: ";
			getline(cin, notes);
			// Update driver notes
			setDriverNotes(notes);
			break;

			case 7:
			break;
    
			default:
			// IF the user invalid choice
			cout << "Invalid choice.\n";
		}
}