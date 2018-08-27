#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
using namespace std;

class Car {
public:
	virtual string get_name() = 0;
	virtual ~Car() {}
};

class Bike {
public:
	virtual string get_name() = 0;
	virtual ~Bike() {}
};



#endif // PRODUCT_H