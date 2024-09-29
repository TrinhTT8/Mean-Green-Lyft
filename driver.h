  //Name: Trinh Tran 			Email: trinhtran3@my.unt.edu\n

#ifndef DRIVER_H
#define DRIVER_H


#include <string>
#include <iostream>

using namespace std;

class Driver {
	
	public:
		Driver(string, string, string, string, int, int, bool, bool, bool, double);			//specified constructor
		
		// Mutator function for driver's information
		void setDriverFName(string Dfname);
		void setDriverLName(string Dlname);
		void setDriverID (int Did);
		void setDriverVehicleType(string Dvehicletype);
		void setDriverVehicleCapacity(int Dvehiclecap);
		void setDriverRating(double Drating);
		void setDriverHandicapped (bool Dhandicapped);
		void setDriverPets(bool Dpets);
		void setDriverAvailability (bool Davailable);
		void setDriverNotes (string Dnotes);

		
		// Accessor functions for driver's information
		string getDriverFName() { return DriverFname; }
		string getDriverLname() { return DriverLname; }
		int getDriverID() { return DriverId; }
		string getDriverVehicleType() { return DriverVehicleType; }
		int getDriverVehicleCapacity() { return DriverVehicleCapacity; }
		double getDriverRating() { return DriverRating; }
		bool getDriverHandicapped() { return DriverHandicapped; }
		bool getDriverPets() { return DriverPets; }
		bool getDriverAvailability () { return DriverAvailability; }
		string getDriverNotes () { return DriverNotes; }
		
		bool CriteriaMatch(int, bool, bool, double);
		
		//Virtual function
		virtual void editDriver();
		virtual void printDriver();
		//Virtual destructor
		virtual ~Driver() {};
		
	private:
		string DriverFname;
		string DriverLname;
		string DriverVehicleType;
		string DriverNotes;
		int DriverId;
		int DriverVehicleCapacity;
		double DriverRating;
		bool DriverHandicapped;
		bool DriverAvailability;
		bool DriverPets;
		
};

#endif