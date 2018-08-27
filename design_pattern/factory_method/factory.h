#include "concrete_product.h"
#include <string>
using namespace std;

class Factory
{
public:
	virtual Car* create_car() = 0;
	virtual ~Factory() {}
};