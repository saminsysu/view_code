#include "component.h"
#include <vector>
using namespace std;

template<typename T> void safe_delete(T*& ptr) {
	if (ptr != nullptr) {
		delete ptr;
		ptr = nullptr;
	}
}

class Composite : public Component
{
public:
	Composite(string name) : Component(name) {}
	~Composite() {
		while (!components.empty()) {
			auto iter = components.begin();
			safe_delete(*iter);
			components.erase(iter);
		}
	}

	virtual void add(Component *component) {
		if (component != nullptr) {
			components.push_back(component);
		}
	}

	virtual void remove(Component *&component) {
		auto iter = components.begin();
		while (iter != components.end()) {
			if (*iter == component) {
				safe_delete(component);
				components.erase(iter);
				return ;
			}
			++iter;
		}
	}
	virtual void show() {
		cout << "in composite: " << name << endl;
		auto iter = components.begin();
		while (iter != components.end()) {
			(*iter) -> show();
			++iter;
		}
	}

private:
	vector<Component *> components;
};