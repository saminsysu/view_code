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