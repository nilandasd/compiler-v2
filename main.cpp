#include <iostream>
#include "token.hpp"

int main() {
	std::cout << "Hello World!" << std::endl;

	Token test(-4);

	std::cout << test.toString() << std::endl;

	return 0;
}
