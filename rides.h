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
		void editRide(vector<Driver*> driList);
		void deleteRide();
		void printAllRide();
		void completeRide(vector<Driver*>& driList);
		Ride* findRide();
		
		// Functions to check for matching driver
		bool checkAvailability(vector<int>, int, int, int, int, int, int);
		vector<int> findAvailableDriver(vector<Driver*>& driList, int, bool, bool, double);
	
		// Functions for data storage
		void storeRide();
		void loadRide();
		void clearRide();
		
		// Functions to manage the number of rides
		Rides() { ridecount = 0; }		// Default constructor
		void inccount();
		void deccount();
		int getcount() { return ridecount; }
		
		// Functions for time
		void convertTime(time_t, int&, int&, int&, int&, int&);		// Convert time to time_t
		time_t getCurrentTime();		// Get the current time
		
		// Function to print rides for passenger and driver
		void printPassRides(vector<Passenger*>& passList);
		void printDriRides(vector<Driver*>& driList);
		
	private:
		int ridecount;
		vector<Ride*> rideList;		// A vector to store ride objects
};

#endif