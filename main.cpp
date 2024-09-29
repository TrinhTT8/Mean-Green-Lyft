//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu\n
//The program implements the Mean Green EagleLyft system. 
//The program allows passengers to schedule rides and drivers to accept rides.
//The program will display a menu that allows for either passengers or drivers to edit their information or rides.

#include <iostream>
#include <string>
#include <iomanip>

#include "passenger.h"
#include "passengers.h"
#include "driver.h"
#include "drivers.h"
#include "rides.h"
#include "ride.h"

using namespace std;

int main ()
{
	//Display name, course, and email
	cout << right << setw(30) << "HOMEWORK 4" << right << setw(30) << "CSCE 1040.001\n";
	cout << right << setw(40) << "Trinh Tran" << right << setw(30) << "trinhtran3@my.unt.edu\n\n";

	cout << "***Welcome to Mean Green EagleLyft***\n";

	//Create passenger, driver and ride objects
	Passengers pass;
	Drivers dri;
	Rides ride;

	//Load the previous passengers, drivers and rides
	pass.loadPass();
	dri.loadDri();
	ride.loadRide();

	int choice = -1;
	char menu;

	//
	do {
		//Display the menu for passengers, drivers and rides
		cout << "\n P - Passengers\n D - Drivers\n R - Rides\n E - Exit\n\n";
		cout << "Where do you want to go: ";
		//Take in user choice
		cin >> menu;
		menu = toupper(menu);
		cin.ignore();
		
		switch(menu) {
		
		//Switch case for is the user choose to go to passengers
		case 'P':
			do {
				cout << "\n------Passengers------\n\n";
				cout << " 0 - Exit\n 1 - Add passenger\n 2 - Edit passenger\n 3 - Delete passenger\n 4 - Print passengers\n 5 - Find passengers\n";
				cout << "\nWhat do you want to do: ";
				cin >> choice;
				cin.ignore();
				switch (choice) {
					//Cases for passenger menu
					case 1: pass.addPass(); break;			//Add a passenger
					case 2: pass.editPass(); break;			//Edit a passenger
					case 3: pass.deletePass(); break;		//Delete a passenger
					case 4: pass.printAllPass(); break;		//Print all passenger
					case 5: pass.findPass(); break;			//Find passenger and print that particular passenger
					default: 
						if (choice == 0){ break;}
						else { cout << "You enter an invalid choice. Please try again...\n"; break; }
				}
			}while (choice != 0);
			break;
		
		case 'D':
			do {
				cout << "------Drivers------\n\n";
				cout << " 0 - Exit\n 1 - Add driver\n 2 - Edit driver\n 3 - Delete driver\n 4 - Print drivers\n 5 - Find drivers\n\n";
				cout << "What do you want to do: ";			
				cin >> choice;
				cin.ignore();
				switch(choice) {
					//Cases for driver menu
					case 1: dri.addDri(); break;		//Add a driver
					case 2: dri.editDri(); break;		//Edit a driver
					case 3: dri.deleteDri(); break;		//Delete a driver
					case 4: dri.printAllDri(); break;	//Print all drivers
					case 5: dri.findDri(); break;		//Find driver and print that particular driver
					default: 
						if (choice == 0){ break;} 
						else { cout << "You enter an invalid choice. Please try again...\n"; break; }
				}
			}while (choice != 0);
			break;
			
		case 'R':
			do {
				cout << "------Rides------\n\n";
				cout << " 0 - Exit\n 1 - Add ride\n 2 - Edit ride\n 3 - Delete ride\n 4 - Print rides\n 5 - Find rides\n 6 - Find driver's rides\n 7 - Find passenger's rides\n 8 - Print schedule\n 9 - Update rides\n\n";
				cout << "What do you want to do: ";
				cin >> choice;
				cin.ignore();
				switch(choice) {
					//Cases for ride menu
					case 1: ride.addRide(pass.getPassList(), dri.getDriList()); break;		//Add a ride
					case 2: ride.editRide(dri.getDriList()); break;							//Edit a ride
					case 3: ride.deleteRide(); break;										//Delete cancelled and completed rides
					case 4: ride.printAllRide(); break;										//Print rides
					case 5: ride.findRide(); break;
					case 6: ride.printDriRides(dri.getDriList()); break;					//Print a particular driver rides
					case 7: ride.printPassRides(pass.getPassList()); break;					//Print a particular passenger rides
					case 9: ride.completeRide(dri.getDriList()); break;
					default: 
						if (choice == 0){ break; }
						else { cout << "You enter an invalid choice. Please try again...\n"; break; }
				}
			}while (choice != 0);
			break;
		
		// The user chooses to exit the program
		case 'E':
			cout << "\nThank you for using Mean Green EagleLyft!\n\n ------Goodbye------\n";
			break;
		
		// The user enter invalid choice
		default:
			cout << "Invalid choice. Please try again...\n";
			break;
		}
	}while (menu != 'E');
		
		//Store passengers, drivers and rides
		pass.storePass();
		dri.storeDri();
		ride.storeRide();
		
		//Clear/deallocate dynamic memory before the program exits
		pass.clearPass();
		dri.clearDri();
		ride.clearRide();
		
	return 0;
	}