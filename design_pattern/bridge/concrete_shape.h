#include "shape.h"
#include <iostream>
using namespace std;

class Triangle : public Shape
{
public:
	Triangle(Color *color) : Shape(color) {}
	virtual void show_shape() {
		cout << "Triangle";
	}
};

class Circle : public Shape
{
public:
	Circle(Color *color) : Shape(color) {}
	virtual void show_shape() {
		cout << "Circle";
	}
};

class Rectangle : public Shape
{
public:
	Rectangle(Color *color) : Shape(color) {}
	virtual void show_shape() {
		cout << "Rectangle";
	}
};