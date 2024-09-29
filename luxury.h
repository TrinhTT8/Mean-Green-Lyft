//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu\n
#ifndef LUXURY_H
#define LUXURY_H

#include "driver.h"
#include <string>

using namespace std;
//Class luxury derived from class Driver
class luxury : public Driver {
    public:
		//Constructor
        luxury (string, string, string, string, int, int, bool, bool, bool, double, int, string, string, string);
        
		//Mutator functions for luxury driver
		void setLuggage(int);
        void setRestrictions(string);
        void setAmenities(string);
        void setType(string);
		
		//Accessor functions for luxury driver
        int getLuggage() {return luggage;}
        string getRestrictions() {return restrictions;}
        string getAmenities() {return amenities;}
        string getType() {return type;}
        
        void editDriver();
        void printDriver();
		//Destructor
        ~luxury() override {};
        
    private:
        int luggage;
        string restrictions;
        string amenities;
        string type; 
};

#endif