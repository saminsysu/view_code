#include "component.h"

class Decoration : public Phone {
public:
	Decoration(Phone *phone) : phone(phone) {}
	virtual ~Decoration() {}
	virtual void show() {
		phone -> show();
		decorate();
	}
	virtual void decorate() = 0;
private:
	Phone *phone;
};