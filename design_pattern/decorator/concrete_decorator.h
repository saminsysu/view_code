#include "decorator.h"

class Shell : public Decoration // 手机壳
{
public:
	Shell(Phone *phone) : Decoration(phone) {}
	virtual void decorate() {
		cout << "	add Shell" << endl;
	}
	
	
};

class Pendant : public Decoration // 挂件
{
public:
	Pendant(Phone *phone) : Decoration(phone) {}
	virtual void decorate() {
		cout << "	add Pendant" << endl;
	}
};