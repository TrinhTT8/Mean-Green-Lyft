//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu

#include "tiereddriver.h"
#include "utils.h"

using namespace std;

TieredDriver::TieredDriver (const string& Dfname, const string& Dlname, const string& Dvehicletype, const string& Dnotes, int Did, int Dvehiclecap, bool Dhandicapped, bool Dpets, bool Davailable, double Drating, int lugcapacity, const string& carRestrict, const string& driType)
: Driver(Dfname, Dlname, Dvehicletype, Dnotes, Did, Dvehiclecap, Dhandicapped, Dpets, Davailable, Drating),
  luggage(lugcapacity), restrictions(carRestrict), type(driType) {}

//Print out the details of the driver
void TieredDriver::printDriver() const {
    Driver::printDriver();      //Calls the base class's print function
    cout << "Driver type: " << getLabel() << "\t\t" << "Luggage capacity: " << luggage << endl;
    cout << "Restrictions: " << restrictions << endl;
    printExtras();
    cout << "Price range: " << getPriceRange() << "\n\n";
}

// Edit details of the driver
void TieredDriver::editDriver() {
    Driver::editDriver();       //Calls the base class's edit function

    cout << "You've signed up for " << getLabel() << " driver type.\n";

    if (askYesNo("Do you want to change your luggage capacity? (Y/N) ")) {
        luggage = askInt("New luggage capacity: ");
    }

    if (askYesNo("Do you want to change your car restrictions? (Y/N) ")) {
        restrictions = askLine("New car restrictions: ");
    }

    editExtras();
}

// Write the type line of drivers.dat: type,luggage,restrictions
void TieredDriver::storeExtras(ostream& out) const {
    out << type << "," << luggage << "," << restrictions;
}
