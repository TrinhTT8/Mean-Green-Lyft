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
		void printAllDri() const;
		Driver* findDri() const;
		vector<Driver*>& getDriList();	// Get the list of drivers

		// Functions for data storage
		void storeDri() const;
		void loadDri();
		void clearDri();

		// The number of drivers
		int getcount() const { return driList.size(); }

	private:
		vector<Driver*> driList;	// A vector to store driver objects
};

#endif
