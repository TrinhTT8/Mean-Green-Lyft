 //Name: Trinh Tran 			Email: trinhtran3@my.unt.edu\n
#ifndef GROUP_H
#define GROUP_H

#include "driver.h"
#include <string>

using namespace std;
//Class group derived from class Driver
class group : public Driver {
    public:
		//Constructor
        group (string, string, string, string, int, int, bool, bool, bool, double, int, string, string);
		
		//Mutator functions for group drivers
        void setLuggage(int);
        void setRestrictions(string);
        void setType(string);
		
		//Accessor functions for group drivers
        int getLuggage() {return luggage;}
        string getRestrictions() {return restrictions;}
        string getType() {return type;}
        
        void editDriver();
        void printDriver();
		//Destructor
        ~group() override{};
		
    private:
        int luggage;
        string restrictions;
        string type;
};

#endif