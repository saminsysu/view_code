#ifndef PHONE_H
#define PHONE_H

#include <iostream>
using namespace std;

class Phone {
public:
	virtual void show() = 0;
	virtual ~Phone() {}
};

#endif