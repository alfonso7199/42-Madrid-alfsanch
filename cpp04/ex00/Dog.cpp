#include "Dog.hpp"

Dog::Dog() : Animal("Dog")
{
	std::cout << "Dog default constructor called" << std::endl;
}

Dog::~Dog()
{
	std::cout << "Dog object " << type << " destroyed" << std::endl;
}

Dog &Dog::operator=(const Dog &other)
{
    std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other)
	{
		Animal::operator=(other);
	}
	return (*this);
}

Dog::Dog(const Dog &other) : Animal(other)
{
    std::cout << "Copy constructor called" << std::endl;
}

void Dog::makeSound() const
{
	std::cout << "Guau Guau" << std::endl;
}