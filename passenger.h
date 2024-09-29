//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu\n

#ifndef PASSENGER_H
#define PASSENGER_H


#include <string>
#include <iostream>

using namespace std;

class Passenger {
	
	public:
		Passenger(string, string, int, string, bool, bool , double);			//specified constructor
		
		//mutator function for passenger's information
		void setPassengerFname(string Pfname);
		void setPassengerLname(string Plname);
		void setPassengerID (int Pid);
		void setPassengerPayment (string Ppay);
		void setPassengerHandicapped (bool Phandicapped);
		void setPassengerRatingRequired(double Prating);
		void setPassengerPets(bool Ppets);
		
		//accessor functions for passenger's information
		string getPassengerFname() { return PassFname; }
		string getPassengerLname() { return PassLname; }
		int getPassengerID() { return PassID; }
		string getPassengerPayment() { return PassPayment; }
		bool getPassengerHandicapped() {return PassHandicapped; }
		double getPassengerRatingRequired() {return PassRatingRequired; }
		bool getPassengerPets() { return PassPets; }
		
		//Print function 
		void printPassenger();
		
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
