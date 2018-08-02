#include "Node.h"
#include <iostream>

class List
{
public:
	List() : head(nullptr), tail(nullptr) {}
	// 增删改查
	void Insert(int val);
	void Erase(int val); // 删除第一个和 val 一样的结点
	void Search(int val);
	int getValueAt(int position);
	void setValueAt(int position, int val);
	void Print();
private:
	Node *head;
	Node *tail;
};