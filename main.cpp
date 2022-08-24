#include <iostream>
#include "tag.hpp"

int main() {
	std::cout << "Hello World!" << std::endl;

	Tag test;
	
	test.id = -4;

	std::cout << test.toString() << std::endl;

	return 0;
}
