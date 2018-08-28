#include "singleton.h"
#include <iostream>

Singleton *Singleton::instance = nullptr;
mutex Singleton::mtx;

Singleton *Singleton::get_instance() {
	if (instance == nullptr) {
		lock_guard<mutex> lock(mtx); // 线程安全，在std::lock_guard对象构造时，传入的mutex对象(即它所管理的mutex对象)会被当前线程锁住。在lock_guard对象被析构时，它所管理的mutex对象会自动解锁，不需要程序员手动调用lock和unlock对mutex进行上锁和解锁操作，而不用担心异常安全问题。
		if (instance == nullptr) {
			instance = new Singleton();
		}
	}
	return instance;
}
