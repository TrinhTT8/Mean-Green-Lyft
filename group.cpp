//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu

#include "group.h"

using namespace std;

group::group (const string& Dfname, const string& Dlname, const string& Dvehicletype, const string& Dnotes, int Did, int Dvehiclecap, bool Dhandicapped, bool Dpets, bool Davailable, double Drating, int lugcapacity, const string& carRestrict)
: TieredDriver(Dfname, Dlname, Dvehicletype, Dnotes, Did, Dvehiclecap, Dhandicapped, Dpets, Davailable, Drating, lugcapacity, carRestrict, "group") {}
