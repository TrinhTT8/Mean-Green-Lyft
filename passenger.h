//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu\n

#ifndef PASSENGER_H
#define PASSENGER_H


#include <string>
#include <iostream>

using namespace std;

class Passenger {

	public:
		Passenger(const string&, const string&, int, const string&, bool, bool , double);			//specified constructor

		//mutator function for passenger's information
		void setPassengerFname(const string& Pfname) { PassFname = Pfname; }
		void setPassengerLname(const string& Plname) { PassLname = Plname; }
		void setPassengerID (int Pid) { PassID = Pid; }
		void setPassengerPayment (const string& Ppay) { PassPayment = Ppay; }
		void setPassengerHandicapped (bool Phandicapped) { PassHandicapped = Phandicapped; }
		void setPassengerRatingRequired(double Prating) { PassRatingRequired = Prating; }
		void setPassengerPets(bool Ppets) { PassPets = Ppets; }

		//accessor functions for passenger's information
		const string& getPassengerFname() const { return PassFname; }
		const string& getPassengerLname() const { return PassLname; }
		int getPassengerID() const { return PassID; }
		const string& getPassengerPayment() const { return PassPayment; }
		bool getPassengerHandicapped() const {return PassHandicapped; }
		double getPassengerRatingRequired() const {return PassRatingRequired; }
		bool getPassengerPets() const { return PassPets; }

		//Print functions
		static void printHeader();		// Column titles
		void printRow() const;			// One row under the column titles
		void printPassenger() const;	// Column titles + row

	private:
		string PassFname;
		string PassLname;
		int PassID;
		string PassPayment;
		bool PassHandicapped;
		double PassRatingRequired;
		bool PassPets;
};

#endif
