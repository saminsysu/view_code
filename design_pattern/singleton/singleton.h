#include <mutex>
using namespace std;

class Singleton {
public:
	static Singleton * get_instance();
	Singleton(const Singleton &) = delete;
	Singleton& operator=(const Singleton &) = delete;

private:
	static Singleton *instance;
	static mutex mtx; 
	Singleton() {}
};