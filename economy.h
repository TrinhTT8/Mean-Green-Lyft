 //Name: Trinh Tran 			Email: trinhtran3@my.unt.edu\n
#ifndef ECONOMY_H
#define ECONOMY_H

#include "tiereddriver.h"
#include <string>

using namespace std;
//Class economy derived from class TieredDriver (which derives from Driver)
class economy : public TieredDriver {
    public:
		//Constructor
        economy (const string&, const string&, const string&, const string&, int, int, bool, bool, bool, double, int, const string&);

		//Destructor
        ~economy() override{};

    protected:
        const char* getLabel() const override { return "Economy"; }
        const char* getPriceRange() const override { return "$-$$"; }
};

#endif
