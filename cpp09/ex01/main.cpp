#include <iostream>
#include "RPN.hpp"

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: usage: ./RPN \"expression\"" << std::endl;
		return 1;
	}

	try
	{
		RPN rpn;
		std::cout << rpn.evaluate(argv[1]) << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}
