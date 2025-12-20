#include "Dog.hpp"

Dog::Dog() : Animal("Dog")
{
	std::cout << "Dog default constructor called" << std::endl;
	brain = new Brain();
}

Dog::~Dog()
{
	std::cout << "Dog object " << type << " destroyed" << std::endl;
	delete brain;
}

Dog &Dog::operator=(const Dog &other)
{
    std::cout << "Dog copy assignment operator called" << std::endl;
	if (this != &other)
	{
		Animal::operator=(other);
		*brain = *other.brain;
	}
	return (*this);
}

Dog::Dog(const Dog &other) : Animal(other)
{
    std::cout << "Dog copy constructor called" << std::endl;
	brain = new Brain(*other.brain);
}

void Dog::makeSound() const
{
	std::cout << "Guau Guau" << std::endl;
}