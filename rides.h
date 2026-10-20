//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu

#ifndef RIDES_H
#define RIDES_H

#include "ride.h"
#include "passenger.h"
#include "driver.h"

#include <vector>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Rides
{
	public:
		// Functions to manage rides
		void addRide(vector<Passenger*>& passList, vector<Driver*>& driList);
		void editRide(const vector<Driver*>& driList);
		void deleteRide();
		void printAllRide() const;
		void completeRide(vector<Driver*>& driList);
		Ride* findRide() const;

		// Functions to check for matching driver
		bool checkAvailability(int driverid, time_t pickupt) const;
		vector<int> findAvailableDriver(const vector<Driver*>& driList, int, bool, bool, double) const;

		// Functions for data storage
		void storeRide() const;
		void loadRide();
		void clearRide();

		// The number of rides
		int getcount() const { return rideList.size(); }

		// Get the current time
		time_t getCurrentTime() const { return time(0); }

		// Function to print rides for passenger and driver
		void printPassRides(const vector<Passenger*>& passList) const;
		void printDriRides(const vector<Driver*>& driList) const;

	private:
		vector<Ride*> rideList;		// A vector to store ride objects
};

#endif
