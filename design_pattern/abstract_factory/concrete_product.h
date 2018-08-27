#include "product.h"
#include <string>
using namespace std;

class BenzCar : public Car
{
public:
	virtual string get_name() {
		return "BenzCar";
	}
};

class BMWCar : public Car
{
public:
	virtual string get_name() {
		return "BMWCar";
	}
};

class AudiCar : public Car
{
public:
	virtual string get_name() {
		return "AudiCar";
	}
};

class BenzBike : public Bike
{
public:
	virtual string get_name() {
		return "BenzBike";
	}
};

class BMWBike : public Bike
{
public:
	virtual string get_name() {
		return "BMWBike";
	}
};

class AudiBike : public Bike
{
public:
	virtual string get_name() {
		return "AudiBike";
	}
};