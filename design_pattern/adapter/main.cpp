#include "adapter.h"
#include <iostream>
using namespace std;

template<typename T> void safe_delete(T*& ptr) {
	if (ptr != nullptr) {
		delete ptr;
		ptr = nullptr;
	}
}

int main() {
	ComputerCharger *com_charger = new Adapter();
	com_charger -> charge();

	safe_delete(com_charger);
}