#include "concrete_color.h"
#include "concrete_shape.h"

template<typename T> void safe_delete(T*& ptr) {
	if (ptr != nullptr) {
		delete ptr;
		ptr = nullptr;
	}
}

int main() {
	Shape *shape;
	Color *red = new Red(), *yellow = new Yellow(), *grey = new Grey();

	shape = new Triangle(red);
	shape -> show();

	safe_delete(shape);

	shape = new Circle(yellow);
	shape -> show();

	safe_delete(shape);

	shape = new Rectangle(grey);
	shape -> show();

	safe_delete(shape);
	safe_delete(red);
	safe_delete(yellow);
	safe_delete(grey);

	return 0;
}
