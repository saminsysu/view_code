#include "factory.h"

class BenzCarFactory : public Factory {
public:
	virtual Car* create_car() {
		return new BenzCar();
	}
};

class BMWCarFactory : public Factory {
public:
	virtual Car* create_car() {
		return new BMWCar();
	}
};

class AudiCarFactory : public Factory {
public:
	virtual Car* create_car() {
		return new AudiCar();
	}
};