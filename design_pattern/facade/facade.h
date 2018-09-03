#include "sub_system.h"

class Facade
{
public:
	void have_a_meal() {
		shopper.buy();
		washer.wash();
		cooker.cook();
		cout << "吃饭" << endl;
	}

private:
	Cooker cooker;
	Shopper shopper;
	Washer washer;
};