//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu

#include "basic.h"

using namespace std;

basic::basic (const string& Dfname, const string& Dlname, const string& Dvehicletype, const string& Dnotes, int Did, int Dvehiclecap, bool Dhandicapped, bool Dpets, bool Davailable, double Drating, int lugcapacity, const string& carRestrict)
: TieredDriver(Dfname, Dlname, Dvehicletype, Dnotes, Did, Dvehiclecap, Dhandicapped, Dpets, Davailable, Drating, lugcapacity, carRestrict, "basic") {}
