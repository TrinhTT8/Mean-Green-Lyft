//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu\n
#ifndef BASIC_H
#define BASIC_H

#include "tiereddriver.h"
#include <string>

using namespace std;

//Class basic derived from class TieredDriver (which derives from Driver)
class basic : public TieredDriver {
    public:
        //Constructor
		basic (const string&, const string&, const string&, const string&, int, int, bool, bool, bool, double, int, const string&);

		//Destructor
        ~basic() override{};

    protected:
        const char* getLabel() const override { return "Basic"; }
        const char* getPriceRange() const override { return "$-$$"; }
};

#endif
