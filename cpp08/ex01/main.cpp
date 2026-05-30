#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Span.hpp"

int main(void)
{
	std::cout << "=== subject example ===" << std::endl;
	{
		Span sp = Span(5);
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);
		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;
	}

	std::cout << "=== overflow test ===" << std::endl;
	{
		Span sp(3);
		sp.addNumber(1);
		sp.addNumber(2);
		sp.addNumber(3);
		try
		{
			sp.addNumber(4);
		}
		catch (std::exception& e)
		{
			std::cout << "Caught: " << e.what() << std::endl;
		}
	}

	std::cout << "=== too few elements ===" << std::endl;
	{
		Span sp(1);
		sp.addNumber(42);
		try
		{
			sp.shortestSpan();
		}
		catch (std::exception& e)
		{
			std::cout << "Caught: " << e.what() << std::endl;
		}
	}

	std::cout << "=== addRange with 10000 numbers ===" << std::endl;
	{
		std::srand(std::time(NULL));
		Span sp(10000);
		std::vector<int> tmp;
		for (int i = 0; i < 10000; ++i)
			tmp.push_back(std::rand());
		sp.addRange(tmp.begin(), tmp.end());
		std::cout << "shortestSpan: " << sp.shortestSpan() << std::endl;
		std::cout << "longestSpan:  " << sp.longestSpan()  << std::endl;
	}

	std::cout << "=== addRange overflow ===" << std::endl;
	{
		Span sp(5);
		std::vector<int> big(10, 1);
		try
		{
			sp.addRange(big.begin(), big.end());
		}
		catch (std::exception& e)
		{
			std::cout << "Caught: " << e.what() << std::endl;
		}
	}

	return 0;
}
