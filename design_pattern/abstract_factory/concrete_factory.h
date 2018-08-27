#include "factory.h"

class BenzFactory : public Factory {
public:
	virtual Car* create_car() {
		return new BenzCar();
	}
	virtual Bike* create_bike() {
		return new BenzBike();
	}
};

class BMWFactory : public Factory {
public:
	virtual Car* create_car() {
		return new BMWCar();
	}
	virtual Bike* create_bike() {
		return new BMWBike();
	}
};

class AudiFactory : public Factory {
public:
	virtual Car* create_car() {
		return new AudiCar();
	}
	virtual Bike* create_bike() {
		return new AudiBike();
	}
};