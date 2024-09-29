//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu

#ifndef RIDE_H
#define RIDE_H

#include "passenger.h"
#include "driver.h"

#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class Ride {
	public:
		Ride (int, int, int, int, string, string, string, double, bool, bool, time_t, time_t);		//specified constructor

		// Mutator function for ride's information
		void setRideId (int);
		void setPickupLoc (string);
		void setDropoffLoc (string);
		void setPartySize (int);
		void setPets (bool);
		void setHandicap (bool);
		void setStatus (string);
		void setRating (double);
		void setPickupT (time_t);
		void setDropoffT (time_t);
		void setPassengerId (int);
		void setDriverId (int);

		// Accessor functions for ride's information		
		int getRideId() { return RideId; }
		string getPickupLoc () { return Pickuploc; }
		string getDropoffLoc () { return Dropoffloc; }
		int getPartySize () { return Partysize; }
		bool getPets () { return Pet; }
		bool getHandicap () { return Handicap; }
		string getStatus () { return Status; }
		double getRating () { return Custrating; }
		time_t getPickupT () { return PickupTime; }
		time_t getDropoffT () { return DropoffTime; }
		int getPassengerId () { return PassId; }
		int getDriverId () { return DriId; }
		
		// Print function
		void printRide();
		
	private:
		int RideId, PassId, DriId, Partysize;
		time_t PickupTime, DropoffTime;
		string Pickuploc, Dropoffloc, Status;
		bool Pet, Handicap;
		double Custrating;

};

#endif
		