#include <iostream>
#include "llist.h"
#include <fstream>

using namespace std;
	LList a;
	a.push_back(1);
	a.push_front(0);
	a.push_back(2);

	std::ofstream test("test.txt");

	test << a;
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
