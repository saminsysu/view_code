#include "color.h"

class Red : public Color {
	virtual string get_color() {
		return "Red";
	}
};

class Yellow : public Color {
	virtual string get_color() {
		return "Yellow";
	}
};

class Grey : public Color {
	virtual string get_color() {
		return "Grey";
	}
};