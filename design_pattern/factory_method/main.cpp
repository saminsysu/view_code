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

	factory = new BenzCarFactory();
	car = factory -> create_car();
	cout << car -> get_name() << endl;

	safe_delete(car);
    safe_delete(factory);

	factory = new BMWCarFactory();
	car = factory -> create_car();
	cout << car -> get_name() << endl;

	safe_delete(car);
    safe_delete(factory);

	factory = new AudiCarFactory();
	car = factory -> create_car();
	cout << car -> get_name() << endl;

	safe_delete(car);
    safe_delete(factory);

	return 0;
}