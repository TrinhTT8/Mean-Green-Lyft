//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu

#include <iostream>
#include "basic.h"
#include "driver.h"
#include "drivers.h"

using namespace std;

basic::basic (string Dfname, string Dlname, string Dvehicletype, string Dnotes, int Did, int Dvehiclecap, bool Dhandicapped, bool Dpets, bool Davailable, double Drating, int lugcapacity, string carRestrict, string driType)
: Driver(Dfname, Dlname, Dvehicletype, Dnotes, Did, Dvehiclecap, Dhandicapped, Dpets, Davailable, Drating) {
    luggage = lugcapacity;
    restrictions = carRestrict; 
}

void basic::setLuggage(int lugcapacity) {
    luggage = lugcapacity;
}

void basic::setRestrictions(string carRestrict) {
    restrictions = carRestrict;
}

void basic::setType(string driType) {
    type = driType;
}

//Print out the details of a basic driver
void basic::printDriver() {
    Driver::printDriver();      //Calls the base class's print function
    cout << "Driver type: Basic" << "\t\t" << "Luggage capacity: " << luggage << endl;
    cout << "Restrictions: " << restrictions << endl;
    cout << "Price range: $-$$\n\n";
}

// Edit details of a 'basic' driver
void basic::editDriver() {
    Driver::editDriver();       //Calls the base class's edit function 
    int lugCap;
    char option;
    string carRestrict;

    cout << "You've signed up for Basic driver type.\n";

    cout << "Do you want to change your luggage capacity? (Y/N) ";
    cin >> option;
    cin.ignore();
    if (option == 'Y' || option == 'y') {
        cout << "New luggage capacity: ";
        cin >> lugCap;
        cin.ignore();
        setLuggage(lugCap);
    }

    cout << "Do you want to change your car restrictions? (Y/N) ";
    cin >> option;
    cin.ignore();
    if (option == 'Y' || option == 'y') {
        cout << "New car restrictions: ";
        getline(cin, carRestrict);
        setRestrictions(carRestrict);
    }
}