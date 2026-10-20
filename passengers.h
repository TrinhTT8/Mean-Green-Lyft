//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu\n

#ifndef PASSENGERS_H
#define PASSENGERS_H

#include <vector>
#include <iostream>
#include "passenger.h"
using namespace std;

class Passengers
{
	public:
		// Functions to manage passengers
		void addPass();
		void editPass();
		void deletePass();
		void printAllPass() const;
		Passenger* findPass() const;
		vector<Passenger*>& getPassList();		// Get the list of passengers

		// Functions for data storage
		void storePass() const;
		void loadPass();
		void clearPass();

	private:
		vector<Passenger*> passList;	// A vector to store passenger objects
};

#endif
