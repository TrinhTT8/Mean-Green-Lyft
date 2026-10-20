//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu\n
#ifndef LUXURY_H
#define LUXURY_H

#include "tiereddriver.h"
#include <string>

using namespace std;
//Class luxury derived from class TieredDriver (which derives from Driver)
class luxury : public TieredDriver {
    public:
		//Constructor
        luxury (const string&, const string&, const string&, const string&, int, int, bool, bool, bool, double, int, const string&, const string&);

		//Mutator and accessor for the luxury-only amenities
        void setAmenities(const string& carAmen) { amenities = carAmen; }
        const string& getAmenities() const { return amenities; }

        void storeExtras(ostream&) const override;
		//Destructor
        ~luxury() override {};

    protected:
        const char* getLabel() const override { return "Luxury"; }
        const char* getPriceRange() const override { return "$$$-$$$$$"; }
        void printExtras() const override;
        void editExtras() override;

    private:
        string amenities;
};

#endif
