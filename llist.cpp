#include "LList.h"
#include <cassert>

LList::Node::Node(const int value, Node* next)
{
	this->value = value;
	this->next = next;
}

LList::Node::~Node() {}

LList::LList()
	:_head(nullptr), _size(0) {}
LList::~LList()
{
	while (_size)
		pop_front();
}
void LList::push_back(int val) {
	
	if (_head == nullptr)
		_head = new Node(val);
	else {
		Node* bufNode = _head;
		while (bufNode->next != nullptr)
			bufNode = bufNode->next;

		bufNode->next = new Node(val);
	}
	_size++;
}
void LList::push_front(int val) {
	_head = new Node (val, _head);
	++_size;
}
void LList::pop_back() {	
	erase_at(_size - 1);
}
void LList::pop_front() {
	erase_at(0);
}
size_t LList::size() const {
	return _size;
}
int& LList::operator[](size_t idx) {
	return getNode(idx)->value;
};    
int  LList::operator[](size_t idx) const {
	return getNode(idx)->value;
}; 
void LList::erase_at(size_t idx) {
	if (idx < 0) {
		assert(idx < 0);
	}
	else if (idx > this->_size - 1) {
		assert(idx > this->_size - 1);
	}

	if (idx == 0) {
		Node* bufNode = _head;
		_head = _head->next;
		delete bufNode;
		_size--;
	}

	else {
		Node* prevNode = this->_head;
		for (size_t i = 0; i < idx - 1; ++i) {
			prevNode = prevNode->next;
		}
		Node* delNode = prevNode->next;
		prevNode->next = delNode->next;
		delete delNode;

		_size--;
	}
}
void LList::insert_at(size_t idx, int val) {
	{
		if (idx < 0) {
			assert(idx < 0);
		}
		else if (idx > this->_size) {
			assert(idx > this->_size);
		}

		if (idx == 0) {
			push_front(val);
		}
		else {
			Node* bufNode = this->_head;
			for (size_t i = 0; i < idx - 1; ++i) {
				bufNode = bufNode->next;
			}
			Node* newNode = new Node(val, bufNode->next);
			bufNode->next = newNode;
			++_size;
		}
	}
}
void LList::reverse() {

	Node* currentNode = _head;
	Node* prevNode = nullptr;
	Node* nextNode = nullptr;

	while (currentNode != nullptr) {
		nextNode = currentNode->next;
		currentNode->next = prevNode;
		prevNode = currentNode;
		currentNode = nextNode;
	}
	_head = prevNode;
}
LList::Node* LList::getNode(int pos) const
{
	if (pos < 0) {
		assert(pos < 0);
	}
	else if (pos >= this->_size) {
		assert(pos >= this->_size);
	}

	Node* bufNode = this->_head;
	for (size_t i = 0; i < pos; ++i) {
		bufNode = bufNode->next;
	}

	return bufNode;
}
