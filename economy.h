 //Name: Trinh Tran 			Email: trinhtran3@my.unt.edu\n
#ifndef ECONOMY_H
#define ECONOMY_H

#include "driver.h"
#include <string>

using namespace std;
//Class economy derived from class Driver
class economy : public Driver {
    public:
		//Constructor
        economy (string, string, string, string, int, int, bool, bool, bool, double, int, string, string);
        
		//Mutator functions for economy drivers
		void setLuggage(int);
        void setRestrictions(string);
        void setType(string);
		
		//Accessor functions for economy drivers
        int getLuggage() {return luggage;}
        string getRestrictions() {return restrictions;}
        string getType() {return type;}
        
        void printDriver();
        void editDriver();
		//Destructor
        ~economy() override{};
		
    private:
        int luggage;
        string restrictions;
        string type;
};

#endif