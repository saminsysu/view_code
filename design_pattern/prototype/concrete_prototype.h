#include "prototype.h"

class Word : public Document {
public:
	Word(string content) : content(content) {}
	virtual Document *clone() {
		return new Word(*this); // 创建一个完全一样的对象
	}
	virtual void edit(string content) {
		this -> content = content;
	}
	virtual string get_content() {
		return content;
	}
private:
	string content;
};

class Excel : public Document {
public:
	Excel(string content) : content(content) {}
	virtual Document *clone() {
		return new Excel(*this); // 创建一个完全一样的对象
	}
	virtual void edit(string content) {
		this -> content = content;
	}
	virtual string get_content() {
		return content;
	}
private:
	string content;
};