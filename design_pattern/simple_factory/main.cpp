#include "factory.h"
#include "product.h"
#include <iostream>
using namespace std;

template<typename T> void safe_delete(T*& ptr) {
	if (ptr != nullptr) {
		delete ptr;
		ptr = nullptr;
	}
}

int main() {
	Factory *factory = new Factory();
	Car *car;
	car = factory -> create_car("BenzCar");
	cout << car -> get_name() << endl;

	safe_delete(car);

	car = factory -> create_car("BMWCar");
	cout << car -> get_name() << endl;

	safe_delete(car);

	car = factory -> create_car("AudiCar");
	cout << car -> get_name() << endl;

	safe_delete(car);
	safe_delete(factory);
	
	return 0;
}