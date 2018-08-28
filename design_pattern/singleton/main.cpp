#include "singleton.h"
#include <iostream>
using namespace std;

int main() {
	Singleton *singleton1 = Singleton::get_instance();
	Singleton *singleton2 = Singleton::get_instance();
	cout << (singleton1 == singleton2) << endl;
}