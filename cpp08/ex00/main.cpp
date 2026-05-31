#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include "easyfind.hpp"

int main(void)
{
	std::cout << "=== vector ===" << std::endl;
	std::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(42);
	v.push_back(5);

	try
	{
		std::vector<int>::iterator it = easyfind(v, 42);
		std::cout << "Found: " << *it << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	try
	{
		easyfind(v, 99);
	}
	catch (std::exception& e)
	{
		std::cout << "Not found: " << e.what() << std::endl;
	}

	std::cout << "=== list ===" << std::endl;
	std::list<int> l;
	l.push_back(10);
	l.push_back(20);
	l.push_back(30);
	try
	{
		std::list<int>::iterator it = easyfind(l, 20);
		std::cout << "Found: " << *it << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	try
	{
		easyfind(l, 99);
	}
	catch (std::exception& e)
	{
		std::cout << "Not found: " << e.what() << std::endl;
	}

	std::cout << "=== deque ===" << std::endl;
	std::deque<int> d;
	d.push_back(7);
	d.push_back(8);
	d.push_back(9);
	try
	{
		std::deque<int>::iterator it = easyfind(d, 8);
		std::cout << "Found: " << *it << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	std::cout << "=== const container ===" << std::endl;
	const std::vector<int> cv(v);
	try
	{
		std::vector<int>::const_iterator it = easyfind(cv, 3);
		std::cout << "Found in const: " << *it << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	return 0;
}
