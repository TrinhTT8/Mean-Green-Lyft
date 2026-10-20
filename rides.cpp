//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu

#include "rides.h"
#include "utils.h"

#include <fstream>
#include <algorithm>
#include <cstdlib>

using namespace std;

// Find the driver with the given ID, or nullptr if there is none
static Driver* findDriverById(const vector<Driver*>& driList, int driverid) {
	for (Driver* driver : driList) {
		if (driver->getDriverID() == driverid) { return driver; }
	}
	return nullptr;
}

// Find the passenger with the given ID, or nullptr if there is none
static Passenger* findPassengerById(const vector<Passenger*>& passList, int passid) {
	for (Passenger* pass : passList) {
		if (pass->getPassengerID() == passid) { return pass; }
	}
	return nullptr;
}

// Number of days in a month (February has 29 days when the year is divisible by 4)
static int daysInMonth(int month, int year) {
	if (month == 2) { return (year % 4 == 0) ? 29 : 28; }
	if (month == 4 || month == 6 || month == 9 || month == 11) { return 30; }
	return 31;
}

// Print every ride that passes the test. Returns true if at least one was printed
template <typename Test>
static bool printMatching(const vector<Ride*>& rideList, Test test) {
	bool ridefound = false;
	for (const Ride* ride : rideList) {
		if (test(ride)) {
			ride->printRide();
			ridefound = true;
		}
	}
	return ridefound;
}

// Delete and remove every ride that passes the test in a single pass over the list
template <typename Test>
static void deleteRidesIf(vector<Ride*>& rideList, Test test) {
	auto newEnd = remove_if(rideList.begin(), rideList.end(), [&](Ride* ride) {
		if (!test(ride)) { return false; }
		delete ride;
		return true;
	});
	rideList.erase(newEnd, rideList.end());
}

// Add rides
void Rides::addRide(vector<Passenger*>& passList, vector<Driver*>& driList) {
	//Prompt user passenger ID until the passenger is found
	Passenger* passenger = nullptr;
	int passid;
	do {
		passid = askInt("Enter passenger ID: ");
		passenger = findPassengerById(passList, passid);
		//Display a message if passenger is not found
		if (passenger == nullptr) {
			cout << "Passenger not found. Please try again...\n\n";
		}
	} while (passenger == nullptr);

	bool handicap = passenger->getPassengerHandicapped();				//Get passenger accessibility
	double requirerating = passenger->getPassengerRatingRequired();		//Get passenger rating required

	//Create ride ID
	int rideid = (rand() % 20000 + 50000);

	//Prompt user for pickup and drop off location
	string pickuploc = askLine("Enter the pickup location: ");
	string dropoffloc = askLine("Enter the drop-off location: ");

	//Prompt user for pet option
	bool pet = askYesNo("Are you bringing pets? (Y/N): ");

	//Get the current date and time
	time_t currentTime = getCurrentTime();
	time_t pickupt;
	bool valid = false;
	int year, month, day, hour, minute;

	//Prompt user for pickup time
	do {
		tm localTime = *localtime(&currentTime);
		year = localTime.tm_year + 1900;

		do {
			cout << "\n**NOTICE: All rides can only be scheduled at most 3 days before the ride.**\n\n";
			cout << "Current year: " << year << endl;
			cout << "Current month: " << localTime.tm_mon + 1 << endl;
			cout << "Current day: " << localTime.tm_mday << endl;
			//Ask the user for the month number
			month = askInt("What month are you scheduling the ride for (1 - 12): ");

			//Check if the month number is valid
			if (month > 12 || month < 1) {
				cout << "Invalid month. Please try again...\n";
			}
		} while (month > 12 || month < 1);

		//Ask use for the day number until it is valid within the chosen month
		while (true) {
			day = askInt("What day are you scheduling the ride for (1 - 30/31): ");
			if (day < 1) {
				cout << "Invalid day. Please try again...\n";
			}
			else if (day > daysInMonth(month, year)) {
				cout << "Invalid day for the selected month. Please try again...\n";
			}
			else { break; }
		}

		//Ask user for the hour and minute to be picked up
		do {
			hour = askInt("For morning, please choose between 0 - 12.\nFor evening, please choose between 13 - 23.\nAt what hour do you want to be pick up: ");
			minute = askInt("Enter the minute (0 - 59): ");

			//Check if the hour and minute entered are valid
			if ((hour < 0 || hour > 23) || (minute < 0 || minute > 59)) {
				cout << "Invalid hour or minute. Please try again...\n";
			}
		} while ((hour < 0 || hour > 23) || (minute < 0 || minute > 59));

		//Get the valid month, day, hour and minute
		tm userPickupT = {};
		userPickupT.tm_year = year - 1900;
        userPickupT.tm_mon = month - 1;
        userPickupT.tm_mday = day;
        userPickupT.tm_hour = hour;
        userPickupT.tm_min = minute;
        userPickupT.tm_isdst = -1;		// Let mktime work out daylight saving time

		pickupt = mktime(&userPickupT);
		double timeDifference = difftime(pickupt, currentTime);

		//Check to see if the chosen pickup time is witin the 3 days range
        if (timeDifference < 0 || timeDifference > 3 * 24 * 60 * 60) {
            cout << "Invalid date or time. You can only schedule a ride for a date and time within 3 days from now.\n";
        }
		else { valid = true;}
	} while (!valid);		//Ask the user to choose another day until the day is valid

	//Ask user for the party size
	int partysize = askInt("How many people is in your party: ");

	//Find driver(s) that matches the criteria and are free at the pickup time (at most 2)
	cout << "\nFinding drivers......\n";
	vector<Driver*> validDrivers;
	for (int driverid : findAvailableDriver(driList, partysize, pet, handicap, requirerating)) {
		if (validDrivers.size() == 2) { break; }
		if (checkAvailability(driverid, pickupt)) {
			validDrivers.push_back(findDriverById(driList, driverid));
		}
	}

	cout << "NOTE: Driver with rating 0 is a new driver.\n";
	if (validDrivers.empty()) {
		cout << "No matching drivers found at the current time.\n";
		return;
	}
	if (validDrivers.size() == 1) {
		cout << "Driver available for your ride:\n";
		validDrivers[0]->printDriver();
	}
	else {
		cout << "Multiple available drivers found.\n";
		for (size_t i = 0; i < validDrivers.size(); i++) {
			cout << "Driver " << i + 1 << endl;
			validDrivers[i]->printDriver();
		}
	}

	//Let the user pick one of the drivers shown
	const string choosePrompt = (validDrivers.size() == 1) ? "Choose one (1): " : "Choose one (1 or 2): ";
	int choice = askInt(choosePrompt);
	while (choice < 1 || choice > (int)validDrivers.size()) {
		cout << "Invalid choice.\n";
		choice = askInt(choosePrompt);
	}
	Driver* selectedDri = validDrivers[choice - 1];
	int driverid = selectedDri->getDriverID();
	cout << "The driver you selected is Driver " << choice << endl;
	selectedDri->printDriver();

	cout << "Selected pickup time: " << ctime(&pickupt) << endl;
	cout << "Driver " << driverid << " has been assigned to your scheduled ride."  << endl;
	cout << "Your ride ID: " << rideid << endl;

	//Status, drop off time and rating are automatically set when the ride is added
	//Populate ride object and add it to the collection
	rideList.push_back(new Ride(rideid, passid, driverid, partysize, pickuploc, dropoffloc, "active", 0, pet, handicap, pickupt, 0));

	//Set the driver as unavailable if the ride starts within 10 minutes
	if (difftime(pickupt, currentTime) <= 600) {
		selectedDri->setDriverAvailability(false);
	}
}

// Check to see if the driver already has an active ride scheduled at the requested time
bool Rides::checkAvailability (int driverid, time_t pickupt) const {
	for (const Ride* ride : rideList) {
		if (ride->getDriverId() == driverid && ride->getStatus() == "active" && ride->getPickupT() == pickupt) {
			return false;
		}
	}
	return true;
}

// Check if the driver has applicable vehicle capacity, pet and handicap policy as well as the required rating
vector<int> Rides::findAvailableDriver(const vector<Driver*>& driList, int partysize, bool pet, bool handicap, double requirerating) const {
	vector<int> matchingDriver;
	for (const Driver* driver : driList) {
		// If the driver meets all the criteria then add the driver to the matching driver vector
		if (driver->CriteriaMatch(partysize, pet, handicap, requirerating)) {
			matchingDriver.push_back(driver->getDriverID());
		}
	}
	return matchingDriver;
}

// Store rides
void Rides::storeRide () const {
	ofstream fout("rides.dat");

	fout << rideList.size() << endl;
	for (const Ride* ride : rideList) {
		fout << ride->getRideId() << "\t" << ride->getPassengerId() << "\t" << ride->getDriverId() << "\t" <<	ride->getPartySize() << "\t" << ride->getPets() << "\t" <<  ride->getHandicap() << "\t" << ride->getStatus() << "\t" << ride->getRating() << endl;
		fout << ride->getPickupLoc() << endl;
		fout << ride->getDropoffLoc() << endl;
		fout << ride->getPickupT() << "\t" << ride->getDropoffT() << endl;
	}
}

// Load rides
void Rides::loadRide() {
	int rideid, driverid, passid, partysize;
	string pickuploc, dropoffloc, status;
	bool pet, handicap;
	double rating;
	time_t pickupt, dropofft;

	ifstream fin("rides.dat");
	//Read in the number of rides
	int count = 0;
	fin >> count;
	fin.ignore();

	for ( int i = 0; i < count && fin; i++) {
        // Read in ride id, passenger id, driver id, party size, pets, handicap, status and rating
        fin >> rideid >> passid >> driverid >> partysize >> pet >> handicap >> status >> rating;
        fin.ignore();

        // Read pickup and dropoff location
        getline(fin, pickuploc);
        getline(fin, dropoffloc);

        // Read pickup and dropoff times
        fin >> pickupt >> dropofft;
        fin.ignore(); // Read and discard the newline

		if (fin) {
			rideList.push_back(new Ride(rideid, passid, driverid, partysize, pickuploc, dropoffloc, status, rating, pet, handicap, pickupt, dropofft));
		}
	}
}

// Clear rides
void Rides::clearRide() {
	for (Ride* ride : rideList) {
		delete ride;
	}
	rideList.clear();
}

// Edit rides
void Rides::editRide(const vector<Driver*>& driList) {
	int searchid = askInt("Enter the ride id: ");

	// Find the ride with the matching ID
	auto found = find_if(rideList.begin(), rideList.end(), [&](const Ride* r) { return r->getRideId() == searchid; });
	if (found == rideList.end()) {
		cout << "Ride not found.\n";
		return;
	}
	Ride* ride = *found;

	if (ride->getStatus() != "active") {
		cout << "Cannot edit completed or cancelled ride.\n";
		return;
	}
	if (getCurrentTime() >= ride->getPickupT()) {
		cout << "Ride " << searchid << " can not be edit because it is in progress. Please cancel it or pick another ride.\n";
		return;
	}

	// The driver assigned to this ride (needed to check capacity and pet policy)
	Driver* driver = findDriverById(driList, ride->getDriverId());
	int option;
	do {
		cout << " 1 - Change pickup location\n 2 - Change drop-off location\n 3 - Change party size\n 4 - Change pets option\n 5 - Cancel ride\n";
		option = askInt("What do you want to do: ");

		switch(option) {
			case 1:
				ride->setPickupLoc(askLine("Enter your new pickup location: "));
				break;

			case 2:
				ride->setDropoffLoc(askLine("Enter your new drop-off location: "));
				break;

			case 3: {
				int newpartysize = askInt("What's your new party size: ");
				if (driver != nullptr && driver->getDriverVehicleCapacity() < newpartysize) {
					cout << "Unable to change party size because driver has insufficient vehicle capacity.\n";
				}
				else {
					ride->setPartySize(newpartysize);
				}
				break;
			}

			case 4: {
				char response = askChar("Are you bringing your pets (Y/N): ");
				if (response == 'Y') {
					if (driver != nullptr && !driver->getDriverPets()) {
						cout << "Unable to change pet option because the driver does not allow pets in the ride.\n";
					}
					else {
						ride->setPets(true);
					}
				}
				else if (response == 'N') {
					ride->setPets(false);
				}
				break;
			}

			case 5:
				if (askYesNo("Ride " + to_string(searchid) + " will be canceled. Please confirm (Y/N): ")) {
					ride->setStatus("cancelled");
				}
				break;

			default:
				cout << "Invalid choice. Please try again...\n";
		}
	} while (option < 1 || option > 5);
}

// Delete rides (can only deleted cancelled or completed rides)
void Rides::deleteRide() {
	// The user gets to choose the delete option (delete one ride, delete cancelled rides or delete completed rides)
	cout << "What do you want to delete?\n 1 - Delete passenger's rides\n 2 - Delete driver's rides\n 3 - Delete a specific ride\n";
	int choice = askInt("Pick an option: ");

	switch (choice) {
		// Delete the cancelled or completed rides of one passenger / one driver
		case 1:
		case 2: {
			bool byPassenger = (choice == 1);
			cout << "Do you want to delete?\n 1 - Cancelled rides\n 2 - Completed rides\n";
			int statusChoice = askInt("Pick an option: ");
			int id = askInt(byPassenger ? "Enter passenger ID: " : "Enter driver ID: ");

			auto belongs = [&](const Ride* r) { return (byPassenger ? r->getPassengerId() : r->getDriverId()) == id; };
			bool found = any_of(rideList.begin(), rideList.end(), belongs);

			if (statusChoice == 1 || statusChoice == 2) {
				const string status = (statusChoice == 1) ? "cancelled" : "completed";
				deleteRidesIf(rideList, [&](const Ride* r) { return belongs(r) && r->getStatus() == status; });
			}
			if (!found) { cout << (byPassenger ? "No matching passenger ID found.\n" : "No matching driver ID found.\n"); }
			break;
		}

		// Delete one ride by its ID
		case 3: {
			int rideid = askInt("Enter ride ID: ");
			bool ridefound = false;
			bool activeride = false;
			for (const Ride* ride : rideList) {
				if (ride->getRideId() == rideid) {
					ridefound = true;
					if (ride->getStatus() == "active") { activeride = true; }
				}
			}

			if (!ridefound) {
				// Display an error message if ride ID cannot be found
				cout << "There is no matching ride with the request.\n";
			}
			// Only completed or cancelled ride can be delete
			else if (activeride) {
				cout << "Can't delete ride " << rideid << endl;
				cout << "Only rides that are completed or cancelled can be delete.\nPlease cancel a ride before deleting it.\n";
			}
			else {
				deleteRidesIf(rideList, [&](const Ride* r) { return r->getRideId() == rideid; });
				cout << "Successfully deleted ride " << rideid << endl;
			}
			break;
		}

		default:
			cout << "There is no matching ride with the request.\n";
	}
}

// Set the status of the ride to complete and update the time
void Rides::completeRide(vector<Driver*>& driList) {
    int searchID = askInt("Enter ride ID: ");

    auto found = find_if(rideList.begin(), rideList.end(), [&](const Ride* r) { return r->getRideId() == searchID; });
    // If the ride doesn't exist
    if (found == rideList.end()) {
    	cout << "Ride with ID " << searchID << " was not found.\n";
    	return;
    }
    Ride* ride = *found;

	// Display a message if the ride has already been marked completed
    if (ride->getStatus() == "completed") {
		cout << "Ride with ID " << searchID << " is already marked as completed.\n";
		return;
    }

	// Set the ride status to completed and update drop-off time with the current time
	ride->setStatus("completed");
	ride->setDropoffT(getCurrentTime());

	// Ask the user for the rating
	ride->setRating(askDouble("Rate your driver (1-5): "));

	// Combine all ratings of the driver's completed rides
	int driverId = ride->getDriverId();
	double sum = 0;
	int numRide = 0;
	for (const Ride* r : rideList) {
		if (r->getDriverId() == driverId && r->getStatus() == "completed") {
			sum += r->getRating();
			numRide++;
		}
	}
	// Set the driver rating to the average rating
	if (Driver* driver = findDriverById(driList, driverId)) {
		driver->setDriverRating(sum / numRide);
	}
	cout << "Ride with ID " << searchID << " has been marked as completed.\n";
}

// Find rides
Ride* Rides::findRide() const {
	bool ridefound = false;

	//Display a search menu to ask what the user is searching for
	cout << "-----Criteria to search for-----\n";
	cout << " I - Ride ID\n C - Vehicle capacity\n H - Handicapped option\n P - Pets option\n R - Rating\n S - Status\n";
	char choice = askChar("What are you looking for? ");

	switch (choice) {
		// A case for finding ride by ride ID
		case 'I': {
			int rideid = askInt("Enter ride ID: ");
			ridefound = printMatching(rideList, [&](const Ride* r) { return r->getRideId() == rideid; });
			break;
		}

		// A case for finding ride by vehicle capacity
		case 'C': {
			int partysize = askInt("Enter the party size of ride: ");
			ridefound = printMatching(rideList, [&](const Ride* r) { return r->getPartySize() == partysize; });
			break;
		}

		// A case for finding ride by handicap option
		case 'H': {
			char answer = askChar("Does the ride has accessibility need (Y/N): ");
			if (answer == 'Y' || answer == 'N') {
				bool wanted = (answer == 'Y');
				ridefound = printMatching(rideList, [&](const Ride* r) { return r->getHandicap() == wanted; });
			}
			break;
		}

		// A case for finding ride by pet option
		case 'P': {
			char answer = askChar("Does the ride has pets (Y/N): ");
			if (answer == 'Y' || answer == 'N') {
				bool wanted = (answer == 'Y');
				ridefound = printMatching(rideList, [&](const Ride* r) { return r->getPets() == wanted; });
			}
			break;
		}

		// A case for finding ride by rating
		case 'R': {
			double rating = askDouble("What is the minimum ride rating (1-5): ");
			ridefound = printMatching(rideList, [&](const Ride* r) { return r->getRating() >= rating; });
			break;
		}

		// A case for finding ride by status
		case 'S': {
			// Prompt the user for the ride status
			cout << " 1 - Active\n 2 - Completed\n 3 - Cancelled\n";
			int option = askInt("");
			static const string statuses[] = { "active", "completed", "cancelled" };
			if (option >= 1 && option <= 3) {
				const string& status = statuses[option - 1];
				ridefound = printMatching(rideList, [&](const Ride* r) { return r->getStatus() == status; });
			}
			break;
		}

		default: cout << "Invalid choice. Please try again...\n";
	}

	if (!ridefound) { cout << "Ride not found.\n"; }
	return nullptr;
}

//Print all rides
void Rides::printAllRide () const {
	//Print out each ride's data
	for (const Ride* ride : rideList) {
		ride->printRide();
	}
	cout << endl;
}

//Print rides for a particular driver
void Rides::printDriRides(const vector<Driver*>& driList) const {
	int driverID = askInt("Enter the driver ID: ");

	if (findDriverById(driList, driverID) == nullptr) {
		cout << "Unable to find driver (ID does not exist).\n";
		return;
	}
	cout << "Rides for driver ID " << driverID << ":" << endl;
	if (!printMatching(rideList, [&](const Ride* r) { return r->getDriverId() == driverID; })) {
		cout << "Driver has no rides yet.\n";
	}
}

//Print rides for a particular passenger
void Rides::printPassRides(const vector<Passenger*>& passList) const {
	int passID = askInt("Enter the passenger ID: ");

	if (findPassengerById(passList, passID) == nullptr) {
		cout << "Unable to find passenger (ID does not exist).\n";
		return;
	}
	cout << "Rides for passenger ID " << passID << ":" << endl;
	if (!printMatching(rideList, [&](const Ride* r) { return r->getPassengerId() == passID; })) {
		cout << "Passenger has no rides yet.\n";
	}
}
