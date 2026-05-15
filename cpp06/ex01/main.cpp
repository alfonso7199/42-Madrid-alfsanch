#include "Serializer.hpp"
#include <iostream>

int main(void)
{
	Data original;
	original.n = 42;
	original.s = "hello";
	original.d = 3.14;

	std::cout << "Original pointer : " << &original << std::endl;
	std::cout << "original.n = " << original.n << std::endl;
	std::cout << "original.s = " << original.s << std::endl;
	std::cout << "original.d = " << original.d << std::endl;

	uintptr_t raw = Serializer::serialize(&original);
	std::cout << "\nSerialized value : " << raw << std::endl;

	Data* restored = Serializer::deserialize(raw);
	std::cout << "\nRestored pointer : " << restored << std::endl;
	std::cout << "restored->n = " << restored->n << std::endl;
	std::cout << "restored->s = " << restored->s << std::endl;
	std::cout << "restored->d = " << restored->d << std::endl;

	std::cout << "\nPointers are equal: " << (restored == &original ? "true" : "false") << std::endl;

	return 0;
}
