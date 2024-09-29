//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu

#include "ride.h"
#include <iomanip>

using namespace std;

// Constructor for the Ride class
Ride::Ride (int rideID, int passID, int driID, int capacity, string pickuploc, string dropoffloc, string status, double rating, bool pet, bool handicap, time_t pickupt, time_t dropofft) {
	// Initialize ride variables with provided values		
	RideId = rideID;
	PassId = passID;
	DriId = driID;
	Partysize = capacity;
	Pickuploc = pickuploc;
	Dropoffloc = dropoffloc; 
	Status = status;
	Pet = pet;
	Handicap = handicap;
	Custrating = rating;
	PickupTime = pickupt;
	DropoffTime = dropofft;
}

// Update ride'ID
void Ride::setRideId (int rideID) { RideId = rideID; }

// Update passenger's ID
void Ride::setPassengerId (int passID) { PassId = passID; }

// Update driver's ID
void Ride::setDriverId (int driID) { DriId = driID; }

// Update pickup location 
void Ride::setPickupLoc (string pickuploc) { Pickuploc = pickuploc; }

// Update drop off location
void Ride::setDropoffLoc (string dropoffloc) { Dropoffloc = dropoffloc; }

// Update party size
void Ride::setPartySize (int partysz) { Partysize = partysz; }

// Update if customer bring pets
void Ride::setPets (bool RidePets) { Pet = RidePets; }

// Update ride's status
void Ride::setStatus (string  RideStatus) { Status = RideStatus; }

// Update ride's rating
void Ride::setRating (double Riderating) { Custrating = Riderating; }

// Update ride pick up time
void Ride::setPickupT (time_t pickupt) { PickupTime = pickupt; }

// Update ride drop off time
void Ride::setDropoffT (time_t dropofft) { DropoffTime = dropofft; }

// Print ride
void Ride::printRide () {
	cout << left << setw(15) << "Ride ID" << left << setw(15) << "Passenger ID" << left << setw(14) << "Driver ID" << left << setw(15) << "Party Size" << left << setw(15) << "Pets option" << left << setw(20) << "Handicap option" << left << setw(12) << "Status" << left << setw(10) << "Rating" << endl;  ;
	cout << left << setw(15) << RideId << left << setw(15) << PassId << left << setw(14) << DriId << left << setw(15) << Partysize;
	if(Pet == 1) {
		cout << left << setw(15) << "Yes";
	}
	else {
		cout << left << setw(15) << "No";
	}
		
	if(Handicap == 1) {
		cout << left << setw(20) << "Yes";
	}
	else {
		cout << left << setw(20) << "No";
	}
	cout << left << setw(12) << Status << left << setw(10) << Custrating << endl;
	
	cout << "Pickup location: " << Pickuploc << endl;
	cout << "Drop-off location: " << Dropoffloc << endl;
	
	// Convert time_t to human format
	char* pickupStr = ctime(&PickupTime);
	char* dropoffStr = ctime(&DropoffTime);
	
	cout << "Pickup time: " << pickupStr;
	cout << "Drop-off time: ";
	// If time_t equals 0, then the ride has not been completed
	if (DropoffTime == 0) { cout << "N/A\n"; }
	else { cout << dropoffStr; }
	cout << endl;
}
	