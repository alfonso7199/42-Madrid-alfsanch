#include <iostream>
#include <string>
#include "iter.hpp"

template <typename T>
void printElem(T const& elem)
{
	std::cout << elem << " ";
}

void doubleInt(int& n)
{
	n *= 2;
}

void toUpper(char& c)
{
	if (c >= 'a' && c <= 'z')
		c = c - 'a' + 'A';
}

int main(void)
{
	int ints[] = {1, 2, 3, 4, 5};
	std::cout << "int array before: ";
	::iter(ints, 5, printElem<int>);
	std::cout << std::endl;

	::iter(ints, 5, doubleInt);
	std::cout << "int array after doubleInt: ";
	::iter(ints, 5, printElem<int>);
	std::cout << std::endl;

	std::string strs[] = {"hello", "world", "42"};
	std::cout << "string array: ";
	::iter(strs, 3, printElem<std::string>);
	std::cout << std::endl;

	const int consts[] = {10, 20, 30};
	std::cout << "const int array: ";
	::iter(consts, 3, printElem<int>);
	std::cout << std::endl;

	char chars[] = {'a', 'b', 'c', 'd'};
	std::cout << "char array before: ";
	::iter(chars, 4, printElem<char>);
	std::cout << std::endl;
	::iter(chars, 4, toUpper);
	std::cout << "char array after toUpper: ";
	::iter(chars, 4, printElem<char>);
	std::cout << std::endl;

	return 0;
}
