//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu

#include <iostream>
#include "luxury.h"
#include "driver.h"

using namespace std;

luxury::luxury (string Dfname, string Dlname, string Dvehicletype, string Dnotes, int Did, int Dvehiclecap, bool Dhandicapped, bool Dpets, bool Davailable, double Drating, int lugcapacity, string carRestrict, string carAmen, string driType)
:Driver(Dfname, Dlname, Dvehicletype, Dnotes, Did, Dvehiclecap, Dhandicapped, Dpets, Davailable, Drating) {
    luggage = lugcapacity;
    restrictions = carRestrict;
    amenities = carAmen; 
}

void luxury::setLuggage(int lugcapacity) {
    luggage = lugcapacity;
}

void luxury::setRestrictions(string carRestrict) {
    restrictions = carRestrict;
}

void luxury::setAmenities(string carAmen) {
    amenities = carAmen; 
}

void luxury::setType(string driType) {
    type = driType;
}

//Print out the details of a group driver
void luxury::printDriver() {
    Driver::printDriver();      //Calls the base class's print function
    cout << "Driver type: Luxury" << "\t\t" << "Luggage capacity: " << luggage << endl;
    cout << "Restrictions: " << restrictions << endl;
    cout << "Special amenities: " << amenities << endl;
    cout << "Price range: $$$-$$$$$\n\n";
}

// Edit details of a luxury driver
void luxury::editDriver() {
    Driver::editDriver();       //Calls the base class's edit function
    int lugCap;
    char option;
    string carRestrict;
    string carAmen;

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
    
    cout << "Do you want to change your car amenities? (Y/N) ";
    cin >> option;
    cin.ignore();
    if (option == 'Y' || option == 'y') {
        cout << "New car amenities: ";
        getline(cin,carAmen);
        setAmenities(carAmen);
    }
}