#ifndef DRIVERS_H
#define DRIVERS_H

#include "driver.h"
#include <iostream>
#include <vector>
using namespace std;

class Drivers
{
	public:	
		// Functions to manage drivers
		void addDri();
	  	void editDri();
		void deleteDri();
		void printAllDri();
		Driver* findDri();
		void printDriRides();
		vector<Driver*>& getDriList();	// Get the list of drivers
		
		// Functions for data storage
		void storeDri();
		void loadDri();
		void clearDri();
		
		// Functions to manage the number of drivers
		Drivers();
		void inccount();
		void deccount();
		int getcount() { return dricount; }
		
	private:
		int dricount;
		vector<Driver*> driList;	// A vector to store driver objects
};

#endif