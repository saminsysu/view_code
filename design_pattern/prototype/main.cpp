#include "concrete_prototype.h"
#include <iostream>
using namespace std;

template<typename T> void safe_delete(T*& ptr) {
	delete ptr;
	ptr = nullptr;
}

int main() {
	Document * doc1;
	Document * doc2;
	string str = "word";

	doc1 = new Word(str);
	doc2 = doc1 -> clone();
	cout << (doc1 == doc2) << endl;
	cout << (doc1 -> get_content() == doc2 -> get_content()) << endl;

	safe_delete(doc1);
	safe_delete(doc2);

	doc1 = new Excel(str);
	doc2 = doc1 -> clone();
	cout << (doc1 == doc2) << endl;
	cout << (doc1 -> get_content() == doc2 -> get_content()) << endl;

	safe_delete(doc1);
	safe_delete(doc2);

	return 0;
}