#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <iostream>
using namespace std;

class Component
{
public:
	Component(string name) : name(name) {}
	virtual ~Component() {}
	virtual void add(Component *) = 0;
	virtual void remove(Component *&) = 0;
	virtual void show() = 0;
protected:
	string name;
};

#endif