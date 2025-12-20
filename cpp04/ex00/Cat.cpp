#include "Cat.hpp"

Cat::Cat() : Animal("Cat")
{
	std::cout << "Cat default constructor called" << std::endl;
}

Cat::~Cat()
{
	std::cout << "Cat object " << type << " destroyed" << std::endl;
}

Cat &Cat::operator=(const Cat &other)
{
    std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other)
	{
		Animal::operator=(other);
	}
	return (*this);
}

Cat::Cat(const Cat &other) : Animal(other)
{
    std::cout << "Copy constructor called" << std::endl;
}

void Cat::makeSound() const
{
	std::cout << "Miau Miau" << std::endl;
}