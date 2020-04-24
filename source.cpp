#include <iostream>
#include "llist.h"
#include <fstream>

using namespace std;

void dump(const LList& l)
{
	for (size_t i = 0; i < l.size(); ++i, cout << " ") cout << l[i];
}

int main()
{
	LList l;
	l.push_back(1);
	l.push_front(0);
	l.push_back(2);

	cout << "Stage 1: "; dump(l); cout << endl;

	l.insert_at(1, 10);
	cout << "Stage 2: "; dump(l); cout << endl;

	l.erase_at(1);
	cout << "Stage 2: "; dump(l); cout << endl;

	l.reverse();
	cout << "Stage 3: "; dump(l); cout << endl;


	std::ofstream test("test.txt");

	test << l;
	test.close();

// обработчик случаев повреждения данных
	LList b;
	try {
		std::ifstream out("otest.txt");
		out.exceptions(std::ifstream::failbit);
		out >> b;
	}
	
	catch (std::ios_base::failure &fail) {
		std::cout <<"Corrapted data:"<< fail.what();
	}
//обработчик ошибки выделения памяти
	try {
		while (true) {
			b.push_back(1);
		}
	}

	catch (const std::bad_alloc & e) {
		std::cout << "Allocation failed: " << e.what() << '\n';
	}

	return 0;
}
