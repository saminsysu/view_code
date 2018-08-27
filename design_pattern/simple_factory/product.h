#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
using namespace std;

class Car {
public:
	virtual string get_name() = 0;
	virtual ~Car() {}
};

#endif // PRODUCT_H