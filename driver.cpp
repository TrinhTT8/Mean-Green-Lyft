//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu

#include "driver.h"
#include "utils.h"
#include <iomanip>

// Constructor for the Driver class
Driver::Driver(const string& Dfname, const string& Dlname, const string& Dvehicletype, const string& Dnotes, int Did, int Dvehiclecap, bool Dhandicapped, bool Dpets, bool Davailable, double Drating)
	// Initialize driver variables with provided values
	: DriverFname(Dfname), DriverLname(Dlname), DriverVehicleType(Dvehicletype), DriverNotes(Dnotes),
	  DriverId(Did), DriverVehicleCapacity(Dvehiclecap), DriverRating(Drating),
	  DriverHandicapped(Dhandicapped), DriverAvailability(Davailable), DriverPets(Dpets) {}

// Check the criteria of specific driver. The function returns true or false
bool Driver::CriteriaMatch(int partysize, bool pet, bool handicap, double requiredrating) const {
	// Check if the driver has enough seats
	if (partysize > DriverVehicleCapacity) { return false; }
    // Check if the driver allows pets
    if (pet && !DriverPets) { return false; }
    // Check if the driver's vehicle is handicap-accessible
    if (handicap && !DriverHandicapped) { return false; }
    // Check if the driver's rating meets the required rating
    if (requiredrating > DriverRating && DriverRating != 0) { return false; }
    // If all criteria are met, return true
    return true;
}

// Print driver's information
void Driver::printDriver () const {
	cout << left << setw(13) << "First name" << setw(13) << "Last name" << setw(8) << "ID" << setw(15) << "Vehicle type" << setw(7) << "Seats" << setw(20) << "Handicapped option" << setw(15) << "Pet option" << setw(10) << "Rating" << setw(15) << "Available" << endl;
	cout << left << setw(13) << DriverFname << setw(13) << DriverLname << setw(8) << DriverId << setw(15) << DriverVehicleType << setw(7) << DriverVehicleCapacity
	     << setw(20) << yesNo(DriverHandicapped) << setw(15) << yesNo(DriverPets) << setw(10) << DriverRating << yesNo(DriverAvailability) << "\n";
	cout << "Notes: " << DriverNotes << endl;
}

void Driver::editDriver() {
	// Ask what category needs to be edit
	cout << " 1 - Name\n 2 - Vehicle Type\n 3 - Vehicle Capacity\n 4 - Handicapped option\n 5 - Pets option\n 6 - Notes\n 7 - Editing driver features\n";
	int option = askInt("What do you want to edit? ");

	switch(option) {
		case 1:
			// Edit name
			DriverFname = askLine("Enter your new first name: ");
			DriverLname = askLine("Enter your new last name: ");
			break;

		case 2:
			// Edit vehicle type
			DriverVehicleType = chooseVehicleType("Choose your new vehicle type: ");
			break;

		case 3:
			// Edit vehicle capacity
			DriverVehicleCapacity = askInt("Enter new vehicle capacity: ");
			break;

		case 4:
			// Edit handicapped option
			DriverHandicapped = askYesNo("Handicap accessiblity options (Y/N): ");
			break;

		case 5:
			// Edit pets option
			DriverPets = askYesNo("Pets option? (Y/N): ");
			break;

		case 6:
			//Edit driver notes
			DriverNotes = askLine("Other informations: ");
			break;

		case 7:
			break;

		default:
			// IF the user invalid choice
			cout << "Invalid choice.\n";
	}
}
