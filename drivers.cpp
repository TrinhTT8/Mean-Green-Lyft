//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu\n

#include "drivers.h"
#include "driver.h"
#include "basic.h"
#include "economy.h"
#include "group.h"
#include "luxury.h"
#include "utils.h"

#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

// Build the right kind of driver from its type name. Returns nullptr for an unknown type
static Driver* createDriver(const string& driType, const string& fname, const string& lname, const string& vehicletype, const string& notes, int id, int vehiclecapacity, bool handicapped, bool pets, bool available, double rating, int lugcapacity, const string& carRestrict, const string& carAmen) {
	if (driType == "basic")   { return new basic(fname, lname, vehicletype, notes, id, vehiclecapacity, handicapped, pets, available, rating, lugcapacity, carRestrict); }
	if (driType == "economy") { return new economy(fname, lname, vehicletype, notes, id, vehiclecapacity, handicapped, pets, available, rating, lugcapacity, carRestrict); }
	if (driType == "group")   { return new group(fname, lname, vehicletype, notes, id, vehiclecapacity, handicapped, pets, available, rating, lugcapacity, carRestrict); }
	if (driType == "luxury")  { return new luxury(fname, lname, vehicletype, notes, id, vehiclecapacity, handicapped, pets, available, rating, lugcapacity, carRestrict, carAmen); }
	return nullptr;
}

// Print every driver that passes the test. Returns true if at least one was printed
template <typename Test>
static bool printMatching(const vector<Driver*>& driList, Test test) {
	bool driverfound = false;
	for (Driver* driver : driList) {
		if (test(driver)) {
			driver->printDriver();
			driverfound = true;
		}
	}
	return driverfound;
}

//Add driver
void Drivers::addDri() {
	// What is shown for each driver type when signing up
	struct DriverTypeInfo { const char* type; const char* heading; const char* price; const char* capacityPrompt; };
	static const DriverTypeInfo typeInfo[] = {
		{ "economy", "--Economy Driver--", "$-$$",   "Vehicle capacity (limit capacity at 2): " },
		{ "basic",   "--Basic Driver--",   "$-$$",   "Vehicle capacity (limit capacity from 2 to 4): " },
		{ "group",   "--Group Driver--",   "$$-$$$", "Vehicle capacity (limit capacity from 5 to 7): " },
		{ "luxury",  "--Luxury Driver--",  "$$-$$$", "Vehicle capacity (limo capacity): " },
	};

	// Prompt user for name
	string fname = askLine("Enter first name: ");
	string lname = askLine("Enter last name: ");

	//  Prompt user for vehicle type
	cout << "What's the vehicle type?\n";
	string vehicletype = chooseVehicleType("Pick one: ");

	// Prompt user for handicap and pet options
	bool handicapped = askYesNo("Handicap accessiblity options (Y/N): ");
	bool pets = askYesNo("Pets option? (Y/N): ");
	bool available = true;

	// Prompt user for additional notes
	string notes = askLine("Other information: ");

	// Automatically assign drive rating to 0 when first added
	double rating = 0;

	// Generate random user ID
	int id = (rand() % 20000 + 30000);

	// Prompt user for the type of driver they signed up for (basic, economy, group, luxury)
	cout << "What type of driver are you?\n";
	cout << " 1. Economy (2 or less passengers)\n 2. Basic (2-4 passengers)\n 3. Group (5-7 passengers)\n 4. Luxury (Limo-style wth amenities)\n";
	int choice = askInt("Choose one: ");
	while (choice < 1 || choice > 4) {
		cout << "Invalid choice\n";
		choice = askInt("Choose one: ");
	}
	const DriverTypeInfo& info = typeInfo[choice - 1];

	cout << info.heading << "\n";
	cout << "  Price: " << info.price << "\n";
	int vehiclecapacity = askInt(info.capacityPrompt);
	int lugcapacity = askInt("Luggage capacity: ");
	string carRestrict = askLine("Car restrictions: ");
	// Only luxury drivers have amenities
	string carAmen;
	if (string(info.type) == "luxury") {
		carAmen = askLine("Car amenities: ");
	}

	// Add object to collection
	driList.push_back(createDriver(info.type, fname, lname, vehicletype, notes, id, vehiclecapacity, handicapped, pets, available, rating, lugcapacity, carRestrict, carAmen));
}

// Store drivers
void Drivers::storeDri () const {
	// Open file for writing
	ofstream fout("drivers.dat");

	if (!fout.is_open()) {
		cout << "Error opening file.\n";
		return;
	}
	// Write the number of drivers
	fout << driList.size() << endl;
	// Loop through the driver list and write the information for each driver
    for (const Driver* driver : driList) {
		// The file will be written in the order of name -> ID -> vehicle type -> vehicle capacity -> handicap -> pet -> rating -> availability -> notes
        fout << driver->getDriverFName() << ","
             << driver->getDriverLname() << ","
             << driver->getDriverID() << ","
             << driver->getDriverVehicleType() << ","
             << driver->getDriverVehicleCapacity() << ","
             << driver->getDriverHandicapped() << ","
             << driver->getDriverPets() << ","
             << driver->getDriverRating() << ","
             << driver->getDriverAvailability() << ","
             << driver->getDriverNotes() << endl;

		// Each driver type writes its own second line (type, luggage, restrictions, ...)
		driver->storeExtras(fout);
		fout << endl;
	}
}

// Load drivers
void Drivers::loadDri() {
	string fname, lname, vehicletype, notes, carRestrict, carAmen, driType;
	int id, vehiclecapacity, lugcapacity;
	bool handicapped, pets, available;
	double rating;

	// Open file for reading
	ifstream fin("drivers.dat");

	int count = 0;
	fin >> count;
	fin.ignore();

	// Loop through the number of drivers and add in the information
    for (int i = 0; i < count && fin; i++) {
		getline(fin, fname, ','); // Read until a comma and store in fname
		getline(fin, lname, ','); // Read until a comma and store in lname
		fin >> id;
		fin.ignore(); // Read and discard the comma
		getline(fin, vehicletype, ','); // Read until a comma and store in vehicletype
		fin >> vehiclecapacity;
		fin.ignore();
		fin >> handicapped;
		fin.ignore();
		fin >> pets;
		fin.ignore();
		fin >> rating;
		fin.ignore();
		fin >> available;
		fin.ignore();
		getline(fin, notes);
		getline(fin, driType, ',');
		fin >> lugcapacity;
		fin.ignore();

		// Luxury drivers store "restrictions.amenities", the others just "restrictions"
		carAmen.clear();
		if (driType == "luxury") {
			getline(fin, carRestrict, '.');
			getline(fin, carAmen);
		}
		else {
			getline(fin, carRestrict);
		}

		Driver* driver = createDriver(driType, fname, lname, vehicletype, notes, id, vehiclecapacity, handicapped, pets, available, rating, lugcapacity, carRestrict, carAmen);
		if (driver != nullptr) { driList.push_back(driver); }
	}
}

// Dealloate the dynnamic memory
void Drivers::clearDri() {
	for (Driver* driver : driList) {
		delete driver;
	}
	driList.clear();
}

//Edit driver
void Drivers::editDri() {
	// Prompt the user for what they want to search for
	SearchKey key = askSearchKey("driver");

	bool driverfound = false;
	// Loop through the driver list
	for (Driver* dri : driList) {
		// If user 's input name or ID is the same as in the driver list
		if (key.matches(dri->getDriverFName(), dri->getDriverLname(), dri->getDriverID())) {
			dri->editDriver();
			driverfound = true;
			cout << "\n*Driver updated information*\n";
			dri->printDriver();
		}
	}
	// Display a message if driver is not found
	if (!driverfound) { cout << "Driver not found.\n";  }
}


// Delete driver
void Drivers::deleteDri() {
	// Let user search by name or ID
	SearchKey key = askSearchKey("driver");

	// Loop through the driver list
	for (auto it = driList.begin(); it != driList.end(); ++it) {
		Driver *dri = *it;
		// If user 's input name or ID is the same as in the driver list
		if (key.matches(dri->getDriverFName(), dri->getDriverLname(), dri->getDriverID())) {
			// Delete the driver information from the collection (name, ID, etc.) if the ID exists
			delete dri;
			driList.erase(it);
			cout << "\nDriver successful deleted.\n";
			return;
		}
	}
	// Return error message if the ID or name  doesn’t exist
	cout << "\nDriver not found.\n";
}

// Find driver based on appropriate criteria
Driver* Drivers::findDri() const {
	bool driverfound = false;

	// Display a search menu to ask what the user is searching for
	cout << "-----Criteria to search for-----\n";
	cout << " N - Name\n I - ID\n T - Vehicle type\n C - Vehicle capacity\n H - Handicapped option\n P - Pets option\n R - Rating\n A - Available\n";
	char choice = askChar("What are you looking for? ");

	switch(choice) {
		// User want to search based on name
		case 'N': {
			string searchFname = askLine("Enter driver first name: ");
			string searchLname = askLine("Enter driver last name: ");
			driverfound = printMatching(driList, [&](Driver* d) {
				return equalsIgnoreCase(d->getDriverFName(), searchFname) && equalsIgnoreCase(d->getDriverLname(), searchLname);
			});
			break;
		}

		// User want to search based on ID
		case 'I': {
			int searchid = askInt("Enter driver ID: ");
			driverfound = printMatching(driList, [&](Driver* d) { return d->getDriverID() == searchid; });
			break;
		}

		// User want to search based on vehicle type
		case 'T': {
			string searchvehicletype = chooseVehicleType("What type of vehicle do you want to search for:");
			driverfound = printMatching(driList, [&](Driver* d) { return d->getDriverVehicleType() == searchvehicletype; });
			break;
		}

		// User want to search based on vehicle capacity
		case 'C': {
			int searchvehiclecap = askInt("What's the vehicle capacity are you looking for? ");
			driverfound = printMatching(driList, [&](Driver* d) { return d->getDriverVehicleCapacity() == searchvehiclecap; });
			break;
		}

		// User want to search based on handicap
		case 'H': {
			bool searchhandicapped = askYesNo("Include accessibility needs or handicaps? (Y/N) ");
			driverfound = printMatching(driList, [&](Driver* d) { return d->getDriverHandicapped() == searchhandicapped; });
			break;
		}

		//User want to search based on pets
		case 'P': {
			bool searchpets = askYesNo("Driver allows pets? (Y/N) ");
			driverfound = printMatching(driList, [&](Driver* d) { return d->getDriverPets() == searchpets; });
			break;
		}

		// User want to search based on default rating required
		case 'R': {
			double searchrating = askDouble("What is the minimum rating you are looking for? ");
			driverfound = printMatching(driList, [&](Driver* d) { return d->getDriverRating() >= searchrating; });
			break;
		}

		// User want to search based on availability
		case 'A': {
			bool searchavail = askYesNo("Are you looking for available drives (Y/N)? ");
			driverfound = printMatching(driList, [&](Driver* d) { return d->getDriverAvailability() == searchavail; });
			break;
		}

		default:
			cout << "Invalid choice\n";
			return nullptr;
	}
	// If no matching driver found
	if (!driverfound) { cout << "No matching drivers found.\n"; }
	return nullptr;
}

// Print all drivers
void Drivers::printAllDri() const {
	// Print out each driver’s data (name, ID, etc.)
	// Call the appropriate overriden function for each type
	for (const Driver* driver : driList) {
        driver->printDriver();
	}
	cout << endl;
}

// Get the drivers vector
vector<Driver*>& Drivers::getDriList() {
	return driList;
}
