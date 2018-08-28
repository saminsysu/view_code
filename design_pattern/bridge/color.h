#ifndef COLOR_H
#define COLOR_H

#include <string>
using namespace std;

class Color
{
public:
	virtual string get_color() = 0;
	virtual ~Color() {}
};

#endif