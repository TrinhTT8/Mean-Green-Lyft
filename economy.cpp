//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu

#include "economy.h"

using namespace std;

economy::economy (const string& Dfname, const string& Dlname, const string& Dvehicletype, const string& Dnotes, int Did, int Dvehiclecap, bool Dhandicapped, bool Dpets, bool Davailable, double Drating, int lugcapacity, const string& carRestrict)
: TieredDriver(Dfname, Dlname, Dvehicletype, Dnotes, Did, Dvehiclecap, Dhandicapped, Dpets, Davailable, Drating, lugcapacity, carRestrict, "economy") {}
