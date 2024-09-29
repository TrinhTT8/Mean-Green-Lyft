//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu\n
#ifndef BASIC_H
#define BASIC_H

#include "driver.h"
#include <string>

using namespace std;

//Class basic derived from class Driver
class basic : public Driver {
    public:
        //Constructor
		basic (string, string, string, string, int, int, bool, bool, bool, double, int, string, string);
        
		//Mutator functions for basic drivers
		void setLuggage(int);
        void setRestrictions(string);
        void setType(string);
		
		//Accessor functions for basic drivers
        int getLuggage() {return luggage;}
        string getRestrictions() {return restrictions;}
        string getType() {return type;}
        
        void editDriver();
        void printDriver();
		
		//Destructor
        ~basic() override{};
		
    private:
        int luggage;
        string restrictions;
        string type;
};

#endif