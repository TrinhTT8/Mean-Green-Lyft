//Name: Trinh Tran 			Email: trinhtran3@my.unt.edu

#ifndef TIEREDDRIVER_H
#define TIEREDDRIVER_H

#include "driver.h"
#include <string>

using namespace std;

// Shared parent of basic, economy, group and luxury drivers.
// Holds the luggage and restriction data that all four types have in common.
class TieredDriver : public Driver {
	public:
		TieredDriver (const string&, const string&, const string&, const string&, int, int, bool, bool, bool, double, int, const string&, const string&);

		//Mutator functions
		void setLuggage(int lugcapacity) { luggage = lugcapacity; }
		void setRestrictions(const string& carRestrict) { restrictions = carRestrict; }
		void setType(const string& driType) { type = driType; }

		//Accessor functions
		int getLuggage() const { return luggage; }
		const string& getRestrictions() const { return restrictions; }
		const string& getType() const { return type; }

		void editDriver() override;
		void printDriver() const override;
		void storeExtras(ostream&) const override;

		~TieredDriver() override {};

	protected:
		// Each driver type fills in its own label and price range
		virtual const char* getLabel() const = 0;		// e.g. "Basic"
		virtual const char* getPriceRange() const = 0;	// e.g. "$-$$"
		// Hooks for types with extra fields (luxury amenities)
		virtual void printExtras() const {}
		virtual void editExtras() {}

	private:
		int luggage;
		string restrictions;
		string type;
};

#endif
