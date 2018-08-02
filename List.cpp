#include "List.h"
#include <iostream>
using namespace std;

void List::Insert(int val) {
	Node * node = new Node(val);
	if (head == nullptr) {
		head = node;
		tail = node;
	} else {
		tail -> next = node;
		tail = node;
	}
}

void List::Erase(int val) { // 删除第一个和 val 一样的结点
	Node *cur = head, *pre = nullptr;
	if (head == nullptr) {
		cout << "the List is empty" << endl;
		return;
	}
	while (cur) {
		if (cur -> val == val) {
			if (pre) {
				pre -> next = cur -> next;
				cout << "delete successfully!" << endl;
				return;
			} else {
				head = head -> next;
			}
			break;
		} else {
			pre = cur;
			cur = cur -> next;
		}
	}
	cout << "not found" << endl;
} 

void List::Search(int val) {
	Node *cur = head;
	int index = 0;
	if (head == nullptr) {
		cout << "the List is empty" << endl;
		return;
	}
	while (cur) {
		if (cur -> val == val) {
			cout << "the value you find is at position " << index << endl;
			return;
		} else {
			cur = cur -> next;
			index++;
		}
	}
	cout << "not found" << endl;
}

int List::getValueAt(int position) {
	Node *cur = head;
	int index = 0;
	if (head == nullptr) {
		cout << "the List is empty" << endl;
		return -1;
	}
	while (index < position && cur) {
		cur = cur -> next;
	}
	if (cur) {
		return cur -> val;
	} else {
		cout << "position is out of range" << endl;
		return -1;
	}	
}

void List::setValueAt(int position, int val) {
	Node *cur = head;
	int index = 0;
	if (head == nullptr) {
		cout << "the List is empty" << endl;
		return;
	}
	while (index < position && cur) {
		cur = cur -> next;
	}
	if (cur) {
		cur -> val = val;
		cout << "set val successfully" << endl;
	} else {
		cout << "position is out of range" << endl;
	}	
}

void List::Print() {
	Node *cur = head;
	if (head == nullptr) {
		cout << "the List is empty" << endl;
		return;
	}
	while (cur) {
		if (cur != tail) {
			cout << cur -> val << ' ';
		} else {
			cout << cur -> val << endl;
		}	
		cur = cur -> next;
	}
}
