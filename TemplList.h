#ifndef LLIST_H
#define LLIST_H

#include <cstddef>
#include <cassert>

template<typename T>

class LList
{
	struct Node {
		Node(const T value, Node* next = nullptr)
		{
			this->value = value;
			this->next = next;
		};

		~Node() {};

		T value;
		Node* next;
	};

public:

	LList();                         // construct new collection
	~LList();                        // free resources

	LList(const LList& copyList);
	LList& operator=(const LList& copyList);
	LList(LList&& moveList) noexcept;
	LList& operator=(LList&& moveList) noexcept;

	void push_back(T val);         // add new value at the end:  [1 2 3 4] -> [1 2 3 4 5]
	void push_front(T val);        // add new value at the begin [1 2 3 4] -> [5 1 2 3 4]
	void pop_back();          // remove at the end          [1 2 3 4] -> [1 2 3]
	void pop_front();         // remove at the front        [1 2 3 4] -> [2 3 4]
	size_t size() const;             // get actual number of items [1 2 3 4] -> 4
	T& operator[](size_t idx);     // get rw access ot specific item addressing by idx
	T  operator[](size_t idx) const; //get read-only access
	void erase_at(size_t idx);       // remove item at specific position: [1 2 3 4], 2 -> [1 2 4]
	void insert_at(size_t idx, T val); // insert item at specific position: [1 2 3 4], 1, 5 -> [1 5 2 3 4]
	void reverse();                  // reverse item sequense: [1 2 3 4] -> [4 3 2 1]
	
	void clear();
	Node* getNode(int pos) const;

	

private:
	Node* _head;
	size_t _size;
};

template<typename T>
LList<T>::LList()
	:_head(nullptr), _size(0) {}

template<typename T>
LList<T>::~LList()
{
	clear();
}

template<typename T>
void LList<T>::clear() {
	while (_size)
		pop_back();
}

template<typename T>
LList<T>::LList(const LList<T>& copyList)
{
	clear();
	this->_size = copyList._size;
	if (this->_size == 0) {
		this->_head = nullptr;
		return;
	}

	this->_head = new Node (copyList._head->value);

	Node* currentNode = this->_head;
	Node* currentCopyNode = copyList._head;

	while (currentCopyNode->next) {
		currentCopyNode = currentCopyNode->next;
		currentNode->next = new Node(currentCopyNode->value);
		currentNode = currentNode->next;
	}
}

template<typename T>
LList<T>& LList<T>::operator=(const LList<T>& copyList)
{
	if (this == &copyList) {
		return *this;
	}

	LList<T>* bufList = new LList<T>(copyList);
	clear();

	this->_size = bufList->_size;
	this->_head = bufList->_head;

	return *this;
}

template<typename T>
LList<T>::LList(LList<T>&& moveList) noexcept
{
	this->_size = moveList._size;
	this->_head = moveList._head;

	moveList._size = 0;
	moveList._head = nullptr;
}

template<typename T>
LList<T>& LList<T>::operator=(LList<T>&& moveList) noexcept
{
	if (this == &moveList) {
		return *this;
	}
	clear();
	this->_size = moveList._size;
	this->_head = moveList._head;

	moveList._size = 0;
	moveList._head = nullptr;

	return *this;
}

template<typename T>
void LList<T>::push_back(T val) {

	if (_head == nullptr)
		_head = new Node(val);
	else {
		Node *bufNode = _head;
		while (bufNode->next != nullptr)
			bufNode = bufNode->next;

		bufNode->next = new Node (val);
	}
	_size++;
}

template<typename T>
void LList<T>::push_front(T val) {
	_head = new Node(val, _head);
	++_size;
}

template<typename T>
void LList<T>::pop_back() {
	erase_at(_size - 1);
}

template<typename T>
void LList<T>::pop_front() {
	erase_at(0);
}

template<typename T>
size_t LList<T>::size() const {
	return _size;
}

template<typename T>
T& LList<T>::operator[](size_t idx) {
	return getNode(idx)->value;
};

template<typename T>
T  LList<T>::operator[](size_t idx) const {
	return getNode(idx)->value;
};

template<typename T>
void LList<T>::erase_at(size_t idx) {

	if (idx < 0) {
		assert(idx < 0);
	}
	else if (idx > this->_size - 1) {
		assert(idx > this->_size - 1);
	}

	if (idx == 0) {
		Node* bufNode = _head->next;
		delete _head;
		_head = bufNode;
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

template<typename T>
void LList<T>::insert_at(size_t idx, T val) {
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

template<typename T>
void LList<T>::reverse() {

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

template<typename T>
typename LList<T>::Node* LList<T>::getNode(int pos) const
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
};

#endif //LLIST_H
