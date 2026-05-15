#include "functions.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

Base* generate(void)
{
	int r = std::rand() % 3;
	if (r == 0) return new A();
	if (r == 1) return new B();
	return new C();
}

void identify(Base* p)
{
	if (dynamic_cast<A*>(p))      std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p)) std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(p)) std::cout << "C" << std::endl;
	else                          std::cout << "unknown" << std::endl;
}

void identify(Base& p)
{
	try { (void)dynamic_cast<A&>(p); std::cout << "A" << std::endl; return; }
	catch (std::exception&) {}
	try { (void)dynamic_cast<B&>(p); std::cout << "B" << std::endl; return; }
	catch (std::exception&) {}
	try { (void)dynamic_cast<C&>(p); std::cout << "C" << std::endl; return; }
	catch (std::exception&) {}
	std::cout << "unknown" << std::endl;
}
