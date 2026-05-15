#include "functions.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main(void)
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	for (int i = 0; i < 6; ++i)
	{
		Base* obj = generate();

		std::cout << "via pointer : ";
		identify(obj);

		std::cout << "via reference: ";
		identify(*obj);

		delete obj;
		std::cout << "---" << std::endl;
	}
	return 0;
}
