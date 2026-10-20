 //Name: Trinh Tran 			Email: trinhtran3@my.unt.edu\n
#ifndef GROUP_H
#define GROUP_H

#include "tiereddriver.h"
#include <string>

using namespace std;
//Class group derived from class TieredDriver (which derives from Driver)
class group : public TieredDriver {
    public:
		//Constructor
        group (const string&, const string&, const string&, const string&, int, int, bool, bool, bool, double, int, const string&);

		//Destructor
        ~group() override{};

    protected:
        const char* getLabel() const override { return "Group"; }
        const char* getPriceRange() const override { return "$$-$$$"; }
};

#endif
