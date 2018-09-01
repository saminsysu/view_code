#include "component.h"

class Leaf : public Component
{
public:
	Leaf(string name) : Component(name) {}
	virtual void add(Component *) {
		cout << "add method is not supported" << endl;
	}

	virtual void remove(Component *&) {
		cout << "remove method is not supported" << endl;
	}

	virtual void show() {
		cout << "leaf: " << name << endl;
	}
	
};