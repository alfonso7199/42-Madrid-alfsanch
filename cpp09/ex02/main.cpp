#include <iostream>
#include "PmergeMe.hpp"

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Error: usage: ./PmergeMe <integers...>" << std::endl;
		return 1;
	}

	try
	{
		PmergeMe pm;
		pm.parseInput(argc, argv);
		pm.display(false);
		pm.sort();
		pm.display(true);
		pm.printTimes();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}
