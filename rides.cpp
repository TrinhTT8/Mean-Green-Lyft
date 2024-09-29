//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu

#include "rides.h"
#include "drivers.h"
#include "passengers.h"

#include <fstream>
#include <cctype>
#include <iomanip>
#include <iterator>

using namespace std;

// A function to get the current time
time_t Rides::getCurrentTime() {
	time_t now = time(0);
	return now;
}

// Increase the number of rides when call
void Rides::inccount() {++ridecount;}

// Decrease the number of rides when call
void Rides::deccount() {--ridecount;}

// Add rides 
void Rides::addRide(vector<Passenger*>& passList, vector<Driver*>& driList) {
	int rideid, passid, driverid, partysize;
	int year, month, day, hour, minute;
	string pickuploc, dropoffloc, status;
	bool pet, handicap;
	double rating, requirerating;
	time_t pickupt, dropofft;
	struct tm userPickupT = {0};

	char response;
	int choice;
	bool passfound = false;
	
	//Create ride, passenger and driver object
	Ride *ride = nullptr;
	Passenger* passenger = nullptr;
	Driver* driver = nullptr;

	do {
		//Prompt user passenger ID
		cout << "Enter passenger ID: ";
		cin >> passid;
		cin.ignore();
		
		//Loop through all passenger
		for (auto it = passList.begin(); it != passList.end(); ++it) {
			Passenger* pass = *it;
			
			//If passenger id found, save it to the passenger object
			if (pass->getPassengerID() == passid) {
					passenger = pass;
					passfound = true;
					break;
			}
		}
		
		//If passenger found...
		if (passfound) {
			string passFname = passenger->getPassengerFname();		//Get passenger first name
			string passLname = passenger->getPassengerLname();		//Get passenger last name
			handicap = passenger->getPassengerHandicapped();		//Get passenger accessibility
			requirerating = passenger->getPassengerRatingRequired();	//Get passenger rating required
		}
		//Display a message if passenger is not found
		else {
			cout << "Passenger not found. Please try again...\n\n";
		}
	} while (!passfound);		//Continue the loop until passenger is found
	
	//Create ride ID 
	srand(time(NULL));
	rideid = (rand() % 20000 + 50000);
	
	//Prompt user for pickup location
	cout << "Enter the pickup location: ";
	getline (cin, pickuploc);
	
	//Prompt user for drop off location
	cout << "Enter the drop-off location: ";
	getline (cin, dropoffloc);
	
	//Prompt user for pet option 
	cout << "Are you bringing pets? (Y/N): ";
	cin >> response;
	cin.ignore();
	
	if (response == 'Y' || response == 'y') { pet = true; }
	else { pet = false; }
	
	//Get the current date and time
	time_t currentTime = time(0);	
	bool valid = false;

	//Prompt user for pickup time
	do {
		do {
			tm* localTime = localtime(&currentTime);
			year = localTime->tm_year + 1900;
			
			//Get the valid date to schedule drive
			struct tm validDate = *localTime;
			validDate.tm_mday += 3;			//Valid date ranges within 3 days from the current time
			mktime(&validDate);
			
			cout << "\n**NOTICE: All rides can only be scheduled at most 3 days before the ride.**\n\n";
			cout << "Current year: " << localTime->tm_year + 1900 << endl;
			cout << "Current month: " << localTime->tm_mon + 1 << endl;
			cout << "Current day: " << localTime->tm_mday << endl;		
			//Ask the user for the month number
			cout << "What month are you scheduling the ride for (1 - 12): ";
			cin >> month;
			cin.ignore();
			
			//Check if the month number is valid
			if (month > 12 || month < 1) { 
				cout << "Invalid month. Please try again...\n";
			}
		} while (month > 12 || month < 1);
		
		//Ask use for the day number
		do {
			cout << "What day are you scheduling the ride for (1 - 30/31): ";
			cin >> day;
			cin.ignore();
			
			//Check if the day is valid within the chosen month
			if (day < 1) {
			cout << "Invalid day. Please try again...\n";
			} 
			else if ((month == 2 && (day > 29 || (day > 28 && year % 4 != 0))) ||
               ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) ||
               (day > 31)) {
				cout << "Invalid day for the selected month. Please try again...\n";
				}
		} while (day < 1 || (month == 2 && (day > 29 || (day > 28 && year % 4 != 0))) || ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) || (day > 31));

		//Ask user for the hour and minute to be picked up
		do {
			cout << "For morning, please choose between 0 - 12.\nFor evening, please choose between 13 - 23.\nAt what hour do you want to be pick up: ";
			cin >> hour;
			cin.ignore();
			cout << "Enter the minute (0 - 59): ";
			cin >> minute;
			cin.ignore();
			
			//Check if the hour and minute entered are valid
			if ((hour < 0 || hour > 23) || (minute < 0 || minute > 59)) { 
				cout << "Invalid hour or minute. Please try again...\n";
			}
		} while ((hour < 0 || hour > 23) || (minute < 0 || minute > 59));
		
		//Get the valid month, day, hour and minute
		userPickupT.tm_year = year - 1900;
        userPickupT.tm_mon = month - 1;
        userPickupT.tm_mday = day;
        userPickupT.tm_hour = hour;
        userPickupT.tm_min = minute;
		
		pickupt = mktime(&userPickupT);
		double timeDifference = difftime(pickupt, currentTime);
		
		//Check to see if the chosen pickup time is witin the 3 days range
        if (timeDifference < 0 || timeDifference > 3 * 24 * 60 * 60) {
            cout << "Invalid date or time. You can only schedule a ride for a date and time within 3 days from now.\n";
        } 
		else { valid = true;}
	} while (!valid);		//Ask the user to choose another day until the day is valid

	//Ask user for the party size
	cout << "How many people is in your party: ";
	cin >> partysize;
	cin.ignore();
	
	//Find driver(s) that matches the criteria
	cout << "\nFinding drivers......\n";
	vector<int> matchingDriver = findAvailableDriver(driList, partysize, pet, handicap, requirerating);
	vector<int> validDrivers;
	
	//Loop through the matchingDriver vector and check who has the appropriate availability
	for (int i = 0; i < matchingDriver.size(); i++) {
		driverid = matchingDriver.at(i);
		bool isAvailable = checkAvailability(matchingDriver, driverid, year, month, day, hour, minute);
		
		//If the function checkAvailability returns true then the valid driver id will be add to the validDrivers vector
		if (isAvailable) {
			validDrivers.push_back(driverid);
		}
	}
	cout << "NOTE: Driver with rating 0 is a new driver.\n";
	if (validDrivers.size() == 0) {
		cout << "No matching drivers found at the current time.\n";
	}
	else if (validDrivers.size() == 1) {
		driverid = validDrivers.at(0);
		cout << "Driver available for your ride:\n";

		for (auto it = driList.begin(); it != driList.end(); ++it) {
			Driver* driver = *it;
			if (driver->getDriverID() == driverid) {
				driver->printDriver();
			}
		}
	}
	else if (validDrivers.size() == 2) {
		cout << "Multiple available drivers found.\n";
		for (int i = 0; i < validDrivers.size(); i++) {
			cout << "Driver " << i + 1 << endl;
			driverid = validDrivers.at(i);
			for (auto it = driList.begin(); it != driList.end(); ++it) {
				Driver* driver = *it;
				if (driver->getDriverID() == driverid) {
				driver->printDriver();
				}
			}
		}
	}
		do {
			cout << "Choose one (1 or 2): ";
			cin >> choice;
			cin.ignore();
			
			if (choice >= 1 && choice <= validDrivers.size()) {
				driverid = validDrivers.at(choice - 1);	
				Driver* selectedDri = nullptr;
				for (auto it = driList.begin(); it != driList.end(); ++it) {
					Driver* driver = *it;
					if (driver->getDriverID() == driverid) {
					selectedDri = driver;
					cout << "The driver you selected is Driver " << choice << endl;
					selectedDri->printDriver();
					}
				}
			}
			else {
				cout << "Invalid choice.\n";
			}
		} while (choice != 1 && choice != 2);
	
	char* date = ctime(&pickupt);
	cout << "Selected pickup time: " << date << endl;	
	cout << "Driver " << driverid << " has been assigned to your scheduled ride."  << endl;
	cout << "Your ride ID: " << rideid << endl;

	//Status, drop off time and rating are automatically set when the ride is added
	status = "active";
	dropofft = 0;
	rating = 0;
	
	//Populate passenger object 
	ride = new Ride(rideid, passid, driverid, partysize, pickuploc, dropoffloc, status, rating, pet, handicap, pickupt, dropofft);
	
	//Add object to collection 
	rideList.push_back(ride);
	inccount();
	
	//Set the availability of the driver is unavailable
	double timeDiff = difftime(pickupt, currentTime);
	if (timeDiff <= 600) {
		for (auto it = driList.begin(); it != driList.end(); ++it) {
			if (driverid == driver->getDriverID()){
				driver->setDriverAvailability(false);
			}
		}
	}
}

// Check to see if the drivers already have scheduled rides at the requested time
bool Rides::checkAvailability (vector<int> machingDriver, int driverid, int year, int month, int day, int hour, int minute) {
	// If the ride list is empty then the driver is automatically available
	if (rideList.empty()) {
		return true;
	}
	// Loop through the ride list to check for time and status
	for (auto it = rideList.begin(); it != rideList.end(); ++it) {
		Ride* ride = *it;
		if (ride->getDriverId() == driverid && ride->getStatus() == "active") {
			time_t scheduledTime = ride->getPickupT();
			int rYear, rMonth, rDay, rHour, rMinute;
			convertTime(scheduledTime, rYear, rMonth, rDay, rHour, rMinute);
			if (year == rYear && month == rMonth && day == rDay && hour == rHour && minute == rMinute) {
				return false;
			}
		}
	}
	return true;		
}

// Check if the driver has applicable vehicle capacity, pet and handicap policy as well as the required rating
vector<int> Rides::findAvailableDriver(vector<Driver*>& driList, int partysize, bool pet, bool handicap, double requirerating) {
	vector<int> matchingDriver;
	// Set the number of driver to 0
	int numDriver = 0;
	
	// Loop through the drive list to find the matching driver
	for (auto it = driList.begin(); it != driList.end() && numDriver <= 2; ++it) {
		Driver* driver = *it;
		int driverid = driver->getDriverID();
			// Check driver vehicle capacity, handicap policy and require rating
			if (driver->CriteriaMatch(partysize, pet, handicap, requirerating)) {
				// If the driver meets all the criteria then add the driver to the matching driver vector
				matchingDriver.push_back(driverid);
				numDriver ++;
			}
	}
	return matchingDriver;
}

// Convert the time_t variable to components
void Rides::convertTime (time_t t, int& year, int& month, int& day, int& minute, int& hour) {
	struct tm* time = localtime(&t);
	year = time->tm_year + 1900; 
	month = time->tm_mon + 1;    
	day = time->tm_mday;
	hour = time->tm_hour;
	minute = time->tm_min;
}

// Store rides
void Rides::storeRide () {
	ofstream fout;
	fout.open("rides.dat");
	
	fout << ridecount << endl;
	Ride *ride;
	for (auto it = rideList.begin(); it != rideList.end(); ++it) {
		ride = *it;
		fout << ride->getRideId() << "\t" << ride->getPassengerId() << "\t" << ride->getDriverId() << "\t" <<	ride->getPartySize() << "\t" << ride->getPets() << "\t" <<  ride->getHandicap() << "\t" << ride->getStatus() << "\t" << ride->getRating() << endl;
		fout << ride->getPickupLoc() << endl;
		fout << ride->getDropoffLoc() << endl;
		fout << ride->getPickupT() << "\t" << ride->getDropoffT() << endl;
		}
	fout.close();
}

// Load rides
void Rides::loadRide() {
	ifstream fin;
	int rideid, driverid, passid, partysize;
	string pickuploc, dropoffloc, status;
	bool pet, handicap;
	double rating;
	time_t pickupt, dropofft;
	
	fin.open("rides.dat");
	//Read in the number of rides
	fin >> ridecount;
	fin.ignore();
	
	for ( int i = 0; i < ridecount; i++) {	
        fin >> rideid;		// Read in ride id
        fin.ignore(); 		
        fin >> passid;		// Read in passenger id
        fin.ignore(); 
        fin >> driverid;	// Read in driver id
        fin.ignore(); 
        fin >> partysize;	// Read in party size
        fin.ignore(); 
        fin >> pet;			// Read in pets option
        fin.ignore(); 
        fin >> handicap;	// Read in handicap needs
        fin.ignore(); 
        fin >> status;		// Read in ride status
        fin.ignore(); 
        fin >> rating;		// Read in rating
        fin.ignore(); 
		
        // Read pickup location
        getline(fin, pickuploc);

        // Read dropoff location
        getline(fin, dropoffloc);

        // Read pickup and dropoff times
        fin >> pickupt;
        fin.ignore(); // Read and discard the comma
        fin >> dropofft;
        fin.ignore(); // Read and discard the newline

		Ride* ride = new Ride(rideid, passid, driverid, partysize, pickuploc, dropoffloc, status, rating, pet, handicap, pickupt, dropofft);
		rideList.push_back(ride);

	}
	fin.close();
}

// Clear rides 
void Rides::clearRide() {
	for (auto it = rideList.begin(); it != rideList.end(); ++it) {
		delete *it;
	}
	rideList.clear();
}

// Edit rides
void Rides::editRide(vector<Driver*> driList) {
	int searchid, vehiclecap, newpartysize; 
	bool petpolicy;
	string newpickup, newdropoff;
	
	time_t currentTime = getCurrentTime();
	
	int option;
	char response;
	
	cout << "Enter the ride id: ";
	cin >> searchid;
	cin.ignore();
	
	Ride* ride;
	Driver* driver;
	
	bool activeride = true;
	for (auto it = rideList.begin(); it != rideList.end(); ++it) {
		ride = *it;
		if (searchid == ride->getRideId() && ride->getStatus() == "active") {
			do {
				if (currentTime < ride->getPickupT()) {
					cout << " 1 - Change pickup location\n 2 - Change drop-off location\n 3 - Change party size\n 4 - Change pets option\n 5 - Cancel ride\n";
					cout << "What do you want to do: ";
					cin >> option;
					cin.ignore();
				
					switch(option) {
						case 1: 
							cout << "Enter your new pickup location: ";
							getline (cin, newpickup);
							ride->setPickupLoc(newpickup);
							break;
							
						case 2:
							cout << "Enter your new drop-off location: ";
							getline (cin, newdropoff);
							ride->setDropoffLoc(newdropoff);
							break;
						
						case 3: 
							cout << "What's your new party size: ";
							cin >> newpartysize;
							cin.ignore();

							for (auto it = driList.begin(); it != driList.end(); ++it) {
								driver = *it;
								if (searchid == driver->getDriverID()) {
									vehiclecap = driver->getDriverVehicleCapacity();
								}
							}
							
							if (vehiclecap < newpartysize) {
								cout << "Unable to change party size because driver has insufficient vehicle capacity.\n";
							}
							else {
								ride->setPartySize(newpartysize);
							}
							break;
							
						case 4:
							cout << "Are you bringing your pets (Y/N): ";
							cin >> response;
							cin.ignore();
							
							if  (response == 'y' || response == 'Y') {
								for (auto it = driList.begin(); it != driList.end(); ++it) {
									driver = *it;
									if (searchid == driver->getDriverID()) {
										petpolicy = driver->getDriverPets();
									}
								}
							
								if (!petpolicy) { 
								cout << "Unable to change pet option because the driver does not allow pets in the ride.\n"; 
								}		
								else if (petpolicy) {
								driver->setDriverPets(true);		// Set the "Pets" property to true
								}
							}
							else if (response == 'n' || response == 'N') {
								driver->setDriverPets(false);
							}
							break;
							
						case 5: 
							cout << "Ride " << searchid << " will be canceled. Please confirm (Y/N): ";
							cin >> response;
							cin.ignore();
							
							if (response == 'y' || response == 'Y') {
								ride->setStatus("cancelled");
							}
							break;
						
						default: 
							cout << "Invalid choice. Please try again...\n";
					}
				}
				else { 
				cout << "Ride " << searchid << " can not be edit because it is in progress. Please cancel it or pick another ride.\n"; }
			} while (option < 1 || option > 5);
		}
		else if (searchid == ride->getRideId() && ride->getStatus() != "active") {
			activeride = false;
		}		
	}
	if (!activeride) { cout << "Cannot edit completed or cancelled ride.\n"; }
}	
			 
// Delete rides (can only deleted cancelled or completed rides)		 
void Rides::deleteRide() {
	bool ridefound = false;
	bool passfound = false;
	bool drifound = false;
	int rideid, passid, driverid;
	int choice;
	
		// The user gets to choose the delete option (delete one ride, delete cancelled rides or delete completed rides)
		cout << "What do you want to delete?\n 1 - Delete passenger's rides\n 2 - Delete driver's rides\n 3 - Delete a specific ride\n";
		cout << "Pick an option: ";
		cin >> choice;
		cin.ignore();
		
		switch (choice) {
			case 1: 
				cout << "Do you want to delete?\n 1 - Cancelled rides\n 2 - Completed rides\n";
				cout << "Pick an option: ";
				cin >> choice;
				cin.ignore();
				cout << "Enter passenger ID: ";
				cin >> passid;
				cin.ignore();
					for (auto it = rideList.begin(); it != rideList.end(); ++it) {
						Ride *ride = *it;
						if (ride->getPassengerId() == passid) {	
							passfound = true;
							if (choice == 1) {
								if (ride->getStatus() == "cancelled") {
									delete ride;
									it = rideList.erase(it);
								}
							}
							if (choice == 2) {
								if (ride->getStatus() == "completed") {
									delete ride;
									it = rideList.erase(it);								
								}
							}
						}
					}
					if (!passfound) { cout << "No matching passenger ID found.\n"; }
				break;
				
			case 2: 
				cout << "Do you want to delete?\n 1 - Cancelled rides\n 2 - Completed rides\n";
				cout << "Pick an option: ";
				cin >> choice;
				cin.ignore();
				cout << "Enter driver ID: ";
				cin >> driverid;
				cin.ignore();
					for (auto it = rideList.begin(); it != rideList.end(); ++it) {
						Ride *ride = *it;
						if (ride->getDriverId() == driverid) {	
							drifound = true;
							if (choice == 1) {
								if (ride->getStatus() == "cancelled") {
									delete ride;
									it = rideList.erase(it);
								}
							}
							if (choice == 2) {
								if (ride->getStatus() == "completed") {
									delete ride;
									it = rideList.erase(it);								
								}
							}
						}
					}
					if (!drifound) { cout << "No matching driver ID found.\n"; }
				break;				
		
			case 3:	
				bool activeride = false;
				cout << "Enter ride ID: ";
				cin >> rideid;
				cin.ignore();	
				for (auto it = rideList.begin(); it != rideList.end(); ++it) {
					Ride *ride = *it;
					if (ride->getRideId() == rideid) {
						ridefound = true;
						if (ride->getStatus() == "cancelled" || ride->getStatus() == "completed") {
							delete ride;
							it = rideList.erase(it);
							cout << "Successfully deleted ride " << rideid << endl;
							}
						else if ( ride->getStatus() == "active") {
							activeride = false;
						}
					}
				}
				// Only completed or cancelled ride can be delete 
				if (activeride) { 
					ridefound = true;
					cout << "Can't delete ride " << rideid << endl;
					cout << "Only rides that are completed or cancelled can be delete.\nPlease cancel a ride before deleting it.\n";
				}
				break;
		}
	// Display an error message if ride ID cannot be found
	if(!ridefound) { cout << "There is no matching ride with the request.\n"; }
}

// Set the status of the ride to complete and update the time
void Rides::completeRide(vector<Driver*>& driList) {
    int searchID, driverId;
	double numRide = 0;
	double sum = 0;
	string status;
	double rate, driverrate;
	bool ridefound = false;
	
    cout << "Enter ride ID: ";
    cin >> searchID;

    // Create an iterator to traverse the rideList vector
    for (auto it = rideList.begin(); it != rideList.end(); ++it) {
        Ride *ride = *it;

        if (ride->getRideId() == searchID) {
			ridefound = true;
            if (ride->getStatus() != "completed") {
				time_t currentT = time(0);
				// Set the ride status to completed
                ride->setStatus("completed");
                // Update drop-off time with the current time
				ride->setDropoffT(currentT);
				
				// Ask the user for the rating
				cout << "Rate your driver (1-5): ";
				cin >> rate;
				cin.ignore();
				// Set the rating for the ride
				ride->setRating(rate);
				// Get the driver ID of the ride
				driverId = ride->getDriverId();
					// Goes through the list of ride again to combine all ratings of the driver
				    for (auto it = rideList.begin(); it != rideList.end(); ++it) {
						Ride *ride = *it;
						// Check to see if the driver ID matches and the ride is completed
						if (driverId == ride->getDriverId() && ride->getStatus() == "completed" ) {
						// Add up all the available ratings
						sum += ride->getRating();
						numRide ++;
						}
					}
					// Calculate the driver rate by finding the average rating
					driverrate = sum/numRide;
					// Traverse through the list of drivers to find the drivers with matching ID
					for (auto it = driList.begin(); it != driList.end(); ++it) {
						Driver *driver = *it;
						if (driverId == driver->getDriverID()) {
							// Set the driver rating once the driver is found
							driver->setDriverRating(driverrate);
						}
					}
				cout << "Ride with ID " << searchID << " has been marked as completed.\n";
				}
			// Display a message if the ride has already been marked completed
			else if (ride->getStatus() == "completed") { 
			cout << "Ride with ID " << searchID << " is already marked as completed.\n"; }
			return;
		}
	}   
    // If the loop completes without finding the ride, it doesn't exist
    if (!ridefound) { cout << "Ride with ID " << searchID << " was not found.\n"; }
}

// Find rides
Ride* Rides::findRide() {
	int rideid, partysize;
	string status;
	double rating;
	
	bool ridefound = false;
	int option;
	char choice;
	
	Ride *ride = nullptr;
	//Display a search menu to ask what the user is searching for 
	cout << "-----Criteria to search for-----\n";
	cout << " I - Ride ID\n C - Vehicle capacity\n H - Handicapped option\n P - Pets option\n R - Rating\n S - Status\n";
	cout << "What are you looking for? ";
	cin >> choice;
	choice = toupper(choice);
	cin.ignore();
	
	switch (choice) {
		// A case for finding ride by ride ID
		case 'I': 
			cout << "Enter ride ID: ";
			cin >> rideid;
			cin.ignore();
			// Loop through the ride list and find the matching ID
			for(auto it = rideList.begin(); it != rideList.end(); it++) {
				if ((*it)->getRideId() == rideid) {
					(*it)->printRide();
					ridefound = true;
				}
			}
			break;
		
		// A case for finding ride by vehicle capacity
		case 'C':
			cout << "Enter the party size of ride: ";
			cin >> partysize;
			cin.ignore();
			// Loop through the ride list and find the matching party size
			for(auto it = rideList.begin(); it != rideList.end(); it++) {
				if ((*it)->getPartySize() == partysize) {
					(*it)->printRide();
					ridefound = true;
				}
			}
			break;
		
		// A case for finding ride by handicap option
		case 'H':
				cout << "Does the ride has accessibility need (Y/N): ";
				cin >> choice;
				cin.ignore();
				choice = toupper(choice);
				for (auto it = rideList.begin(); it != rideList.end(); it++) {
					if ((choice == 'Y') && ((*it)->getHandicap() == true)) {
						(*it)->printRide();
						ridefound = true;
					}
					else if ((choice == 'N') && ((*it)->getHandicap() == false)) {
						(*it)->printRide();
						ridefound = true;
					}
				}
			break;
			
		// A case for finding ride by pet option
		case 'P':
				cout << "Does the ride has pets (Y/N): ";
				cin >> choice;
				cin.ignore();
				choice = toupper(choice);
				for(auto it = rideList.begin(); it != rideList.end(); it++) {
					if (choice == 'Y'|| (*it)->getPets() == true) {
						(*it)->printRide();
						ridefound = true;					
					}
					else if ((choice == 'N') && ((*it)->getPets() == false)) {
						(*it)->printRide();
						ridefound = true;					
					}
				}
			break;
		
		// A case for finding ride by rating
		case 'R':
			cout << "What is the minimum ride rating (1-5): ";
			cin >> rating;
			cin.ignore();
				for(auto it = rideList.begin(); it != rideList.end(); it++) {
					if ((*it)->getPets() >= rating) {
						(*it)->printRide();
						ridefound = true;									
					}
				}
			break;
			
		case 'S':
			// Prompt the user for the ride status
			cout << " 1 - Active\n 2 - Completed\n 3 - Cancelled\n";
			cin >> option;
			cin.ignore();
				
				switch (option) {
					// Find active rides
					case 1:
						for(auto it = rideList.begin(); it != rideList.end(); it++) {
							if ((*it)->getStatus() == "active") {
								(*it)->printRide();
								ridefound = true;									
							}
						}
					break;
					
					// Find completed rides
					case 2:
						for(auto it = rideList.begin(); it != rideList.end(); it++) {
							if ((*it)->getStatus() == "completed") {
								(*it)->printRide();
								ridefound = true;									
							}
						}
						break;
					
					// Find cancelled rides
					case 3:
						for(auto it = rideList.begin(); it != rideList.end(); it++) {
							if ((*it)->getStatus() == "cancelled") {
								(*it)->printRide();
								ridefound = true;									
							}
						}
						break;
				}
			break;
		
		default: cout << "Invalid choice. Please try again...\n";
	}
			
	if (ridefound) { return ride; }
	else { cout << "Ride not found.\n"; return nullptr; }
}

//Print all rides
void Rides::printAllRide () {
	for (auto it = rideList.begin(); it != rideList.end(); ++it) {
		
	//Access the driver object from the iterator
	Ride *ride = *it;
	
	//Print out each driver’s data (name, ID, etc.) 
	ride->printRide();
	}
	cout << endl;
}

//Print rides for a particular driver
void Rides::printDriRides(vector<Driver*>& driList) {
    int driverID;
	bool driverfound = false;
	cout << "Enter the driver ID: ";
	cin >> driverID;
	cin.ignore();
	int numride = 0;
	
    for (auto it = driList.begin(); it != driList.end(); ++it) {
		Driver* driver = *it;
		if (driver->getDriverID() == driverID) {
			cout << "Rides for driver ID " << driverID << ":" << endl;

			for (auto it = rideList.begin(); it != rideList.end(); ++it) {
				Ride* ride = *it;

				if (ride->getDriverId() == driverID) {
					// Print ride details here
					ride->printRide();
					driverfound = true;
					++ numride;
				}
			}
			if (numride == 0) {
				cout << "Driver has no rides yet.\n";
				driverfound = true;
			}
		}
	}
	if (!driverfound) { cout << "Unable to find driver (ID does not exist).\n"; }
}

//Print rides for a particular passenger
void Rides::printPassRides(vector<Passenger*>& passList) {
    int passID;
	int numride = 0;
	bool passfound = false;
	cout << "Enter the passenger ID: ";
	cin >> passID;
	cin.ignore();
	
    for (auto it = passList.begin(); it != passList.end(); ++it) {
		Passenger* passenger = *it;
		if (passenger->getPassengerID() == passID) {
			cout << "Rides for passenger ID " << passID << ":" << endl;

			for (auto it = rideList.begin(); it != rideList.end(); ++it) {
				Ride* ride = *it;

				if (ride->getPassengerId() == passID) {
					// Print ride details here
					ride->printRide();
					passfound = true;
				}
			}
			if (numride == 0) {
				cout << "Passenger has no rides yet.\n";
				passfound = true;
			}
		}
	}
	if (!passfound) { cout << "Unable to find passenger (ID does not exist).\n"; }
}