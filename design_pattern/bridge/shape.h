#ifndef SHAPE_H
#define SHAPE_H

#include "color.h"
#include <iostream>
using namespace std;

class Shape
{
public:
	Shape(Color *color) : color(color) {}
	virtual void show() {
		show_shape();
		cout << ' ';
		show_color();
		cout << endl;
	}
	virtual void show_shape() = 0;
	virtual void show_color() {
		cout << color -> get_color();
	}
	virtual ~Shape() {}
private:
	Color *color;
};

#endif