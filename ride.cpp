//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu

#include "ride.h"
#include "utils.h"
#include <iomanip>

using namespace std;

// Constructor for the Ride class
Ride::Ride (int rideID, int passID, int driID, int capacity, const string& pickuploc, const string& dropoffloc, const string& status, double rating, bool pet, bool handicap, time_t pickupt, time_t dropofft)
	// Initialize ride variables with provided values
	: RideId(rideID), PassId(passID), DriId(driID), Partysize(capacity),
	  PickupTime(pickupt), DropoffTime(dropofft),
	  Pickuploc(pickuploc), Dropoffloc(dropoffloc), Status(status),
	  Pet(pet), Handicap(handicap), Custrating(rating) {}

// Print ride
void Ride::printRide () const {
	cout << left << setw(15) << "Ride ID" << setw(15) << "Passenger ID" << setw(14) << "Driver ID" << setw(15) << "Party Size" << setw(15) << "Pets option" << setw(20) << "Handicap option" << setw(12) << "Status" << setw(10) << "Rating" << endl;
	cout << left << setw(15) << RideId << setw(15) << PassId << setw(14) << DriId << setw(15) << Partysize
	     << setw(15) << yesNo(Pet) << setw(20) << yesNo(Handicap) << setw(12) << Status << setw(10) << Custrating << endl;

	cout << "Pickup location: " << Pickuploc << endl;
	cout << "Drop-off location: " << Dropoffloc << endl;

	// Convert time_t to human format
	cout << "Pickup time: " << ctime(&PickupTime);
	cout << "Drop-off time: ";
	// If time_t equals 0, then the ride has not been completed
	if (DropoffTime == 0) { cout << "N/A\n"; }
	else { cout << ctime(&DropoffTime); }
	cout << endl;
}
