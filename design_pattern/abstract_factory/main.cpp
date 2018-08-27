#include "product.h"
#include "concrete_factory.h"
#include <iostream>
using namespace std;

template<typename T> void safe_delete(T*& ptr) {
	delete ptr;
	ptr = nullptr;
}

int main() {
	Factory *factory;
	Car *car;
	Bike *bike;

	factory = new BenzFactory();
	car = factory -> create_car();
	bike = factory -> create_bike();
	cout << car -> get_name() << endl;
	cout << bike -> get_name() << endl;

	safe_delete(car);
	safe_delete(bike);
    safe_delete(factory);

	factory = new BMWFactory();
	car = factory -> create_car();
	bike = factory -> create_bike();
	cout << car -> get_name() << endl;
	cout << bike -> get_name() << endl;

	safe_delete(car);
	safe_delete(bike);
    safe_delete(factory);

	factory = new AudiFactory();
	car = factory -> create_car();
	bike = factory -> create_bike();
	cout << car -> get_name() << endl;
	cout << bike -> get_name() << endl;

	safe_delete(car);
	safe_delete(bike);
    safe_delete(factory);
    
	return 0;
}