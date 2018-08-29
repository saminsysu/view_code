#include "component.h"

class Iphone : public Phone {
public:
	virtual void show() {
		cout << "Iphone" << endl;
	}
};

class Huawei : public Phone {
public:
	virtual void show() {
		cout << "Huawei" << endl;
	}
};