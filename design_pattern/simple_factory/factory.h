#include "concrete_product.h"
#include <string>
using namespace std;

class Factory
{
public:
	Car* create_car(string car_type) {
		Car* car;
		if (car_type == "BenzCar") {
			car =  new BenzCar();
		} else if (car_type == "BMWCar") {
			car = new BMWCar();
		} else if (car_type == "AudiCar") {
			car = new AudiCar(); 
		}
		return car;
	}
};