//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu\n

#ifndef DRIVER_H
#define DRIVER_H


#include <string>
#include <iostream>

using namespace std;

class Driver {

	public:
		Driver(const string&, const string&, const string&, const string&, int, int, bool, bool, bool, double);			//specified constructor

		// Mutator function for driver's information
		void setDriverFName(const string& Dfname) { DriverFname = Dfname; }
		void setDriverLName(const string& Dlname) { DriverLname = Dlname; }
		void setDriverID (int Did) { DriverId = Did; }
		void setDriverVehicleType(const string& Dvehicletype) { DriverVehicleType = Dvehicletype; }
		void setDriverVehicleCapacity(int Dvehiclecap) { DriverVehicleCapacity = Dvehiclecap; }
		void setDriverRating(double Drating) { DriverRating = Drating; }
		void setDriverHandicapped (bool Dhandicapped) { DriverHandicapped = Dhandicapped; }
		void setDriverPets(bool Dpets) { DriverPets = Dpets; }
		void setDriverAvailability (bool Davailable) { DriverAvailability = Davailable; }
		void setDriverNotes (const string& Dnotes) { DriverNotes = Dnotes; }


		// Accessor functions for driver's information
		const string& getDriverFName() const { return DriverFname; }
		const string& getDriverLname() const { return DriverLname; }
		int getDriverID() const { return DriverId; }
		const string& getDriverVehicleType() const { return DriverVehicleType; }
		int getDriverVehicleCapacity() const { return DriverVehicleCapacity; }
		double getDriverRating() const { return DriverRating; }
		bool getDriverHandicapped() const { return DriverHandicapped; }
		bool getDriverPets() const { return DriverPets; }
		bool getDriverAvailability () const { return DriverAvailability; }
		const string& getDriverNotes () const { return DriverNotes; }

		bool CriteriaMatch(int, bool, bool, double) const;

		//Virtual function
		virtual void editDriver();
		virtual void printDriver() const;
		// Writes the line of type-specific data that follows the common data in drivers.dat
		virtual void storeExtras(ostream&) const {}
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
