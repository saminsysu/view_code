#include "concrete_decorator.h"
#include "concrete_component.h"

template<typename T> void safe_delete(T*& ptr) {
	delete ptr;
	ptr = nullptr;
}

int main() {
	Phone *decoration1, *decoration2;
	Phone *phone;
	phone = new Iphone();
	decoration1 = new Shell(phone);
	decoration1 -> show();
	decoration2 = new Pendant(decoration1);
	decoration2 -> show();

	safe_delete(phone);
	safe_delete(decoration1);
	safe_delete(decoration2);

	phone = new Huawei();
	decoration1 = new Shell(phone);
	decoration1 -> show();
	decoration2 = new Pendant(decoration1);
	decoration2 -> show();

	safe_delete(phone);
	safe_delete(decoration1);
	safe_delete(decoration2);

	return 0;
}