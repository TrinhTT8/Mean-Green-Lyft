//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu

#include "luxury.h"
#include "utils.h"

using namespace std;

luxury::luxury (const string& Dfname, const string& Dlname, const string& Dvehicletype, const string& Dnotes, int Did, int Dvehiclecap, bool Dhandicapped, bool Dpets, bool Davailable, double Drating, int lugcapacity, const string& carRestrict, const string& carAmen)
: TieredDriver(Dfname, Dlname, Dvehicletype, Dnotes, Did, Dvehiclecap, Dhandicapped, Dpets, Davailable, Drating, lugcapacity, carRestrict, "luxury"),
  amenities(carAmen) {}

// Printed between the restrictions and the price range
void luxury::printExtras() const {
    cout << "Special amenities: " << amenities << endl;
}

// Asked after the luggage and restriction questions
void luxury::editExtras() {
    if (askYesNo("Do you want to change your car amenities? (Y/N) ")) {
        amenities = askLine("New car amenities: ");
    }
}

// drivers.dat line: luxury,luggage,restrictions.amenities
void luxury::storeExtras(ostream& out) const {
    TieredDriver::storeExtras(out);
    out << "." << amenities;
}
