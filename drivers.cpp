//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu\n

#include "drivers.h"
#include "driver.h"
#include "basic.h"
#include "economy.h"
#include "group.h"
#include "luxury.h"

#include <string>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <iterator>

using namespace std;

Drivers::Drivers() : dricount(0) {}

// Increase the driver count by one if call
void Drivers::inccount() {dricount++;}

// Decrease the driver count by one if call
void Drivers::deccount() {dricount--;}

//Add driver 
void Drivers::addDri() {
	string fname;
	string lname;
	string vehicletype;
	string notes;
	string carRestrict;
	string carAmen;
	string driType;
	int id;
	int vehiclecapacity;
	int lugcapacity;
	double rating;
	bool handicapped;
	bool pets;
	bool available;
	
	char response;
	int choice;
	//Create driver object
	Driver *driver;
	
	// Prompt user for name 
	cout << "Enter first name: ";
	getline(cin, fname);
	
	cout << "Enter last name: ";
	getline(cin, lname);
		
	//  Prompt user for vehicle type
	cout << "What's the vehicle type?\n";
	cout << "1 - Convertible\n2 - Coupe\n3 - Compact\n4 - Crossover\n5 - Electric\n6 - Hatchback\n7 - Hybrid\n8 - Minivan\n9 - Sedan\n10 - SUV\n11 - Truck\n12 - Limo\n";
	cout << "Pick one: ";
	cin >> choice;
	cin.ignore();
	// Switch case that corresponds to the user choice
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
	
	// Prompt user for handicap option
	cout << "Handicap accessiblity options (Y/N): ";
	cin >> response;
	cin.ignore();
	
	if (response == 'Y' || response == 'y') { handicapped = true; }
	else { handicapped = false; }
	
	// Prompt user for pet option 
	cout << "Pets option? (Y/N): ";
	cin >> response;
	cin.ignore();
	
	if (response == 'Y' || response == 'y') { pets = true; }
	else { pets = false; }
	
	available = true;
	
	// Prompt user for additional notes
	cout << "Other information: ";
	getline(cin, notes);

	// Automatically assign drive rating to 0 when first added	
	rating = 0;
	
	// Generate random user ID 
	srand(time(NULL));
	id = (rand() % 20000 + 30000);
	
	// Prompt user for the type of driver they signed up for (basic, economy, group, luxury	
	cout << "What type of driver are you?\n";
	cout << " 1. Economy (2 or less passengers)\n 2. Basic (2-4 passengers)\n 3. Group (5-7 passengers)\n 4. Luxury (Limo-style wth amenities)\n";
	cout << "Choose one: ";
	cin >> choice;
	cin.ignore();
		switch(choice) {
			case 1:
				driType = "economy";
				cout << "--Economy Driver--\n";
				cout << "  Price: $-$$\n";
				// Prompt user for vehicle capacity
				cout << "Vehicle capacity (limit capacity at 2): ";
				cin >> vehiclecapacity;
				cin.ignore();
				// Prompt user for luggage capacity
				cout << "Luggage capacity: ";
				cin >> lugcapacity;
				cin.ignore();
				//Prompt user for car restrictions
				cout << "Car restrictions: ";
				getline(cin, carRestrict);
				//Populate driver of type basic 
				driver = new economy(fname, lname, vehicletype, notes, id, vehiclecapacity, handicapped, pets, available, rating, lugcapacity, carRestrict, driType);
				break;
			case 2:
				driType = "basic";
				cout << "--Basic Driver--\n";
				cout << "  Price: $-$$\n";
				cout << "Vehicle capacity (limit capacity from 2 to 4): ";
				cin >> vehiclecapacity;
				cin.ignore();
				cout << "Luggage capacity: ";
				cin >> lugcapacity;
				cin.ignore();
				cout << "Car restrictions: ";
				getline(cin, carRestrict);
				driver = new basic(fname, lname, vehicletype, notes, id, vehiclecapacity, handicapped, pets, available, rating, lugcapacity, carRestrict, driType);
				break;
			case 3:
				driType = "group";
				cout << "--Group Driver--\n";
				cout << "  Price: $$-$$$\n";
				cout << "Vehicle capacity (limit capacity from 5 to 7): ";
				cin >> vehiclecapacity;
				cin.ignore();
				cout << "Luggage capacity: ";
				cin >> lugcapacity;
				cin.ignore();
				cout << "Car restrictions: ";
				getline(cin, carRestrict);
				driver = new group(fname, lname, vehicletype, notes, id, vehiclecapacity, handicapped, pets, available, rating, lugcapacity, carRestrict, driType);
				break;
			case 4:
        driType = "luxury";
				cout << "--Luxury Driver--\n";
				cout << "  Price: $$-$$$\n";
				cout << "Vehicle capacity (limo capacity): ";
				cin >> vehiclecapacity;
				cin.ignore();
				cout << "Luggage capacity: ";
				cin >> lugcapacity;
				cin.ignore();
				cout << "Car restrictions: ";
				getline(cin, carRestrict);
				// Prompt user for car amenities
				cout << "Car amenities: ";
				getline(cin, carAmen);
				driver = new luxury(fname, lname, vehicletype, notes, id, vehiclecapacity, handicapped, pets, available, rating, lugcapacity, carRestrict, carAmen, driType);
				break;
			default:
				cout << "Invalid choice\n";
				break;
		}
	
	// Add object to collection 
	driList.push_back(driver);
	// Increase driver count
	inccount();
}

// Store drivers
void Drivers::storeDri () {
	ofstream fout;
	// Open file for writing
	fout.open("drivers.dat");
		
	if (!fout.is_open()) {
		cout << "Error opening file.\n";
	}
	// Write the number of drivers
	fout << dricount <<endl;
	Driver* driver;
	// Loop through the driver list and write the information for each driver
    for (auto it = driList.begin(); it != driList.end(); ++it) {
        driver = *it;
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
		
		//Storing each type of driver
		if (auto ptr = dynamic_cast<basic*>(*it)) 
		{
          	basic *temp = dynamic_cast <basic*>(*it);  
			fout << "basic," << temp->getLuggage() << "," << temp->getRestrictions() << endl; }
       	else if (auto ptr = dynamic_cast<economy*>(*it))
    	{
          	economy *temp = dynamic_cast <economy*>(*it);
			fout << "economy," << temp->getLuggage() << "," << temp->getRestrictions() << endl; }
       else if (auto ptr = dynamic_cast<group*>(*it))
        {
         	group *temp = dynamic_cast <group*>(*it);
			fout << "group," << temp->getLuggage() << "," << temp->getRestrictions() << endl; }
		else if (auto ptr = dynamic_cast<luxury*>(*it))
		{
			luxury *temp = dynamic_cast <luxury*>(*it);
			fout << "luxury," << temp->getLuggage() << "," << temp->getRestrictions() << "." << temp->getAmenities() << endl; }
		}	
	fout.close();
}

// Load drivers
void Drivers::loadDri() {
	ifstream fin;
	string fname, lname, vehicletype, notes, carRestrict, carAmen, driType;
	int id, vehiclecapacity, lugcapacity;
	bool handicapped, pets, available;
	double rating;
	
	string firstline;
	// Open file for reading
	fin.open("drivers.dat");
	
	fin >> dricount;
	fin.ignore();

	// Loop through the number of drivers and add in the information
    for (int i = 0; i < dricount; i++) {
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

      	if (driType == "basic")
      	{
			fin >> lugcapacity;
			fin.ignore();
			getline(fin, carRestrict);
			//Add in the basic driver object
	  		driList.push_back(new basic(fname, lname, vehicletype, notes, id, vehiclecapacity, handicapped, pets, available, rating, lugcapacity, carRestrict, driType)); }
    	else if (driType == "economy")
     	{
			fin >> lugcapacity;
			fin.ignore();
			getline(fin, carRestrict);
			//Add in the economy driver object
			driList.push_back( new economy (fname, lname, vehicletype, notes, id, vehiclecapacity, handicapped, pets, available, rating, lugcapacity, carRestrict, driType)); }  
     	else if (driType == "group")
     	{
			fin >> lugcapacity;
			fin.ignore();
			getline(fin, carRestrict);
			// Add in the group driver object
			driList.push_back( new group (fname, lname, vehicletype, notes, id, vehiclecapacity, handicapped, pets, available, rating, lugcapacity, carRestrict, driType)); }
		else if (driType == "luxury")
		{
			fin >> lugcapacity;
			fin.ignore();
			getline(fin, carRestrict, '.');
			getline(fin, carAmen);
			// Add in the luxury driver object
			driList.push_back( new luxury (fname, lname, vehicletype, notes, id, vehiclecapacity, handicapped, pets, available, rating, lugcapacity, carRestrict, carAmen, driType)); }
     	}    
	fin.close();
}

// Dealloate the dynnamic memory
void Drivers::clearDri() {
	for (auto it = driList.begin(); it != driList.end(); ++it) {
		delete *it;
	}
	driList.clear();
}
// Make this a virtual function and have other child classes have an edit function. Work like a virtual print function.
//Edit driver
void Drivers::editDri() {
	string fname;
	string lname;
	int choice;

	
	// Prompt the user for what they want to search for
	cout << "What do you want to search by: 1 - Name\t 2 - ID\nEnter your choice: ";
	cin >> choice;
	cin.ignore();
	
	string searchFname;
	string searchLname;
	int searchid;
	
	// User choose to find the driver by name
	if (choice == 1) {
		cout << "Enter driver first name: ";
		getline(cin, searchFname);
		// Switch all the letters to lowercase for comparison
		for (int i = 0; i < searchFname.length(); ++i) {
			searchFname[i] = tolower(searchFname[i]);
		}
		cout << "Enter driver last name: ";
		getline(cin, searchLname);
		for (int i = 0; i < searchLname.length(); ++i) {
			searchLname[i] = tolower(searchLname[i]);
		}
	}
	// User choose to find the driver by ID
	else {
		cout << "Enter driver ID: ";
		cin >> searchid;
	}  
	
	bool driverfound;
	string storeFname;
	string storeLname;
	// Loop through the driver list 
	for (auto it = driList.begin(); it != driList.end(); ++it) {
		Driver *dri = *it;
		// Get the driver name
		storeFname = dri->getDriverFName();
		storeLname = dri->getDriverLname();
		// Switch all the letters to lowercase for comparison		
		for (int i = 0; i < storeFname.length(); ++i) {
			storeFname[i] = tolower(storeFname[i]);
		}	
		for (int i = 0; i < storeLname.length(); ++i) {
			storeLname[i] = tolower(storeLname[i]);
		}
		
		// If user 's input name or ID is the same as in the driver list 
		if ( (storeFname == searchFname) && (storeLname == searchLname ) || ( dri->getDriverID() == searchid) )
		{
			(*it)->editDriver();
			driverfound= true;
			cout << "\n*Driver updated information*\n";
			(*it)->printDriver();
		}
	}
	// Display a message if driver is not found	
	if (!driverfound) { cout << "Driver not found.\n";  }
}


// Have a destructor in the child class and drivers class
// Delete driver 
void Drivers::deleteDri() {
	
	string searchFname;
	string searchLname;
	string storeFname;
	string storeLname;
	bool driverfound = false;
	int searchid;
	int choice;
	
	// Let user search by name or ID
	cout << "What do you want to search by: 1 - Name\t 2 - ID\nEnter your choice: ";
	cin >> choice;
	cin.ignore();
	

	// User choose to find the driver by name
	if (choice == 1) {
		cout << "Enter driver first name: ";
		getline(cin, searchFname);
		for (int i = 0; i < searchFname.length(); ++i) {
			searchFname[i] = tolower(searchFname[i]);
		}
		cout << "Enter driver last name: ";
		getline(cin, searchLname);
		for (int i = 0; i < searchLname.length(); ++i) {
			searchLname[i] = tolower(searchLname[i]);
		}
	}
	// User choose to find the driver by ID
	else {
		cout << "Enter driver ID: ";
		cin >> searchid;
	} 
	// Loop through the driver list
	for (auto it = driList.begin(); it != driList.end(); ++it) {
		Driver *dri = *it;
		// Check if driver exists
		storeFname = dri->getDriverFName();
		storeLname = dri->getDriverLname();
		
		for (int i = 0; i < storeFname.length(); ++i) {
			storeFname[i] = tolower(storeFname[i]);
		}
		
		for (int i = 0; i < storeLname.length(); ++i) {
			storeLname[i] = tolower(storeLname[i]);
		}
		// If user 's input name or ID is the same as in the driver list 
		if ( (storeFname == searchFname) && (storeLname == searchLname ) || ( dri->getDriverID() == searchid) )
		{
		// Delete the driver information from the collection (name, ID, etc.) if the ID exists 
			delete dri;
			it = driList.erase(it);
			driverfound = true;
			cout << "\nDriver successful deleted.\n";
			deccount();
			return;
		}	
	}
	// Return error message if the ID or name  doesn’t exist  
	if ( !driverfound ) { cout << "\nDriver not found.\n"; }
}

// Find driver based on appropriate criteria 
Driver* Drivers::findDri() {
	string searchFname;
	string searchLname;
	string storeFname;
	string storeLname;
	string searchvehicletype;
	int searchid, searchvehiclecap;
	bool searchhandicapped, searchpets, searchavail;
	double searchrating;
	
	bool driverfound = false;
	int option;
	char choice;
	
	Driver *dri = nullptr;
	// Display a search menu to ask what the user is searching for 
	cout << "-----Criteria to search for-----\n";
	cout << " N - Name\n I - ID\n T - Vehicle type\n C - Vehicle capacity\n H - Handicapped option\n P - Pets option\n R - Rating\n A - Available\n";
	cout << "What are you looking for? ";
	cin >> choice;
	choice = toupper(choice);
	cin.ignore();

	switch(choice) {
		// User want to search based on name
		case 'N':
			cout << "Enter driver first name: ";
			getline(cin, searchFname);
			for (int i = 0; i < searchFname.length(); ++i) {
				searchFname[i] = tolower(searchFname[i]);
			}
			cout << "Enter driver last name: ";
			getline(cin, searchLname);
			for (int i = 0; i < searchLname.length(); ++i) {
				searchLname[i] = tolower(searchLname[i]);
			}
			for(auto it = driList.begin(); it != driList.end(); it++) {
				storeFname = (*it)->getDriverFName();
				storeLname = (*it)->getDriverLname();
		
				for (int i = 0; i < storeFname.length(); ++i) {
					storeFname[i] = tolower(storeFname[i]);
				}
				for (int i = 0; i < storeLname.length(); ++i) {
					storeLname[i] = tolower(storeLname[i]);
				}	
				if ((storeFname == searchFname) && (storeLname== searchLname)) {
						(*it)->printDriver();
						driverfound = true;
				}			
			}
				if (!driverfound) { cout << "No matching drivers found.\n"; }
			break;
		
		// User want to search based on ID
		case 'I':
			cout << "Enter driver ID: ";
			cin >> searchid;
			cin.ignore();
			
			for(auto it = driList.begin(); it != driList.end(); it++) {
				if ((*it)->getDriverID() == searchid) {
					(*it)->printDriver();
					driverfound = true;
				}
			}
			if (!driverfound) { cout << "No matching driver found.\n"; }
			break;
		
		// User want to search based on vehicle type
		case 'T':
			cout << "1 - Convertible\n2 - Coupe\n3 - Compact\n4 - Crossover\n5 - Electric\n6 - Hatchback\n7 - Hybrid\n8 - Minivan\n9 - Sedan\n10 - SUV\n11 - Truck\n12 - Limo\n";
			cout << "What type of vehicle do you want to search for:";
			cin >> option;
			cin.ignore();
			switch (option) {
				case 1: searchvehicletype = "convertible"; break;
				case 2: searchvehicletype = "coupe"; break;
				case 3: searchvehicletype = "compact"; break;
				case 4: searchvehicletype = "crossover"; break;
				case 5: searchvehicletype = "electric"; break;
				case 6: searchvehicletype = "hatchback"; break;
				case 7: searchvehicletype = "hybrid"; break;
				case 8: searchvehicletype = "minivan"; break;
				case 9: searchvehicletype = "sedan"; break;
				case 10: searchvehicletype = "suv"; break;
				case 11: searchvehicletype = "truck"; break;
				case 12: searchvehicletype = "limo"; break;
				default: cout << "Invalid choice"; break;
				}
				
			for(auto it = driList.begin(); it != driList.end(); it++) {
				if ((*it)->getDriverVehicleType() == searchvehicletype) {
					if ( typeid(**it) == typeid(basic) )
					(*it)->printDriver();
					driverfound = true;
				}
			}
			if (!driverfound) { cout << "No matching drivers found.\n"; }
			break;
		// User want to search based on vehicle capacity
		case 'C':
			cout << "What's the vehicle capacity are you looking for? ";
			cin >> searchvehiclecap;
			cin.ignore();
				
			for(auto it = driList.begin(); it != driList.end(); it++) {
				if ((*it)->getDriverVehicleCapacity() == searchvehiclecap) {
					if ( typeid(**it) == typeid(basic) )
					(*it)->printDriver();
					driverfound = true;
				}
			}
			if (!driverfound) { cout << "No matching drivers found.\n"; }
			break;
			
		// User want to search based on handicap
		case 'H':
			cout << "Include accessibility needs or handicaps? (Y/N) ";
			cin >> choice;
			
			if ( choice == 'y' || choice == 'Y' ) { searchhandicapped = true; }
			else { searchhandicapped = false; }
			
			for(auto it = driList.begin(); it != driList.end(); it++) {
				if ((*it)->getDriverHandicapped() == searchhandicapped) {
					if ( typeid(**it) == typeid(basic) )
					(*it)->printDriver();
					driverfound = true;
				}
			}
			if (!driverfound) { cout << "No matching drivers found.\n"; }
			break;
		
		//User want to search based on pets
		case 'P':
			cout << "Driver allows pets? (Y/N) ";
			cin >> choice;
			
			if ( choice == 'y' || choice == 'Y' ) { searchpets = true; }
			else { searchpets = false; }
			
			for(auto it = driList.begin(); it != driList.end(); it++) {
				if ((*it)->getDriverPets() == searchpets) {
					(*it)->printDriver();
					driverfound = true;
				}
			}
			if (!driverfound) { cout << "No matching drivers found.\n"; }
			break;
		
		// User want to search based on default rating required
		case 'R':
			cout << "What is the minimum rating you are looking for? ";
			cin >> searchrating;
			cin.ignore();
			
			for(auto it = driList.begin(); it != driList.end(); it++) {
				if ((*it)->getDriverRating() >= searchrating) {
					(*it)->printDriver();
					driverfound = true;
				}
			}
			// If no matching driver found
			if (!driverfound) { cout << "No matching drivers found.\n"; }
			break;
			
		// User want to search based on availability
		case 'A':
			cout << "Are you looking for available drives (Y/N)? ";
			cin >> choice;
			cin.ignore();
			if ( choice == 'y' || choice == 'Y' ) { searchavail = true; }
			else { searchavail = false; }
			
			for(auto it = driList.begin(); it != driList.end(); it++) {
				if ((*it)->getDriverAvailability() == searchavail) {
					(*it)->printDriver();
					driverfound = true;
				}
			}
			if (!driverfound) { cout << "No matching drivers found.\n"; }
			break;
		
		default: cout << "Invalid choice\n"; break;
			
	}
	// Return the driver object
	return dri;
} 

// Print all drivers
void Drivers::printAllDri() {	
	// Iterate through each driver in Driver list 
	for (auto it = driList.begin(); it != driList.end(); ++it) {
		// Print out each driver’s data (name, ID, etc.)
		// Call the appropriate overriden function for each type
        (*it)->printDriver();
	}
	cout << endl;
}

// Get the drivers vector 
vector<Driver*>& Drivers::getDriList() { 
	return driList; 
}
