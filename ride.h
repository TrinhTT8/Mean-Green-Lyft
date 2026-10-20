//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu

#ifndef RIDE_H
#define RIDE_H

#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class Ride {
	public:
		Ride (int, int, int, int, const string&, const string&, const string&, double, bool, bool, time_t, time_t);		//specified constructor

		// Mutator function for ride's information
		void setRideId (int rideID) { RideId = rideID; }
		void setPickupLoc (const string& pickuploc) { Pickuploc = pickuploc; }
		void setDropoffLoc (const string& dropoffloc) { Dropoffloc = dropoffloc; }
		void setPartySize (int partysz) { Partysize = partysz; }
		void setPets (bool RidePets) { Pet = RidePets; }
		void setHandicap (bool RideHandicap) { Handicap = RideHandicap; }
		void setStatus (const string& RideStatus) { Status = RideStatus; }
		void setRating (double Riderating) { Custrating = Riderating; }
		void setPickupT (time_t pickupt) { PickupTime = pickupt; }
		void setDropoffT (time_t dropofft) { DropoffTime = dropofft; }
		void setPassengerId (int passID) { PassId = passID; }
		void setDriverId (int driID) { DriId = driID; }

		// Accessor functions for ride's information
		int getRideId() const { return RideId; }
		const string& getPickupLoc () const { return Pickuploc; }
		const string& getDropoffLoc () const { return Dropoffloc; }
		int getPartySize () const { return Partysize; }
		bool getPets () const { return Pet; }
		bool getHandicap () const { return Handicap; }
		const string& getStatus () const { return Status; }
		double getRating () const { return Custrating; }
		time_t getPickupT () const { return PickupTime; }
		time_t getDropoffT () const { return DropoffTime; }
		int getPassengerId () const { return PassId; }
		int getDriverId () const { return DriId; }

		// Print function
		void printRide() const;

	private:
		int RideId, PassId, DriId, Partysize;
		time_t PickupTime, DropoffTime;
		string Pickuploc, Dropoffloc, Status;
		bool Pet, Handicap;
		double Custrating;

};

#endif
