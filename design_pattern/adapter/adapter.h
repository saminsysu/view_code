#include "target.h"
#include "adaptee.h"
#include <iostream>

class Adapter : public ComputerCharger {
public:
	virtual void charge() {
		charger -> ChargeForComputer();
	}
	Adapter() : charger(new Charger()) {}
	~Adapter() {
		delete charger;
		charger = nullptr;
	}
private:
	Charger *charger;
};