#include "Cat.hpp"

Cat::Cat() : Animal("Cat")
{
	std::cout << "Cat default constructor called" << std::endl;
	brain = new Brain();
}

Cat::~Cat()
{
	std::cout << "Cat object " << type << " destroyed" << std::endl;
	delete brain;
}

Cat &Cat::operator=(const Cat &other)
{
    std::cout << "Cat copy assignment operator called" << std::endl;
	if (this != &other)
	{
		Animal::operator=(other);
		*brain = *other.brain;
	}
	return (*this);
}

Cat::Cat(const Cat &other) : Animal(other)
{
    std::cout << "Cat copy constructor called" << std::endl;
	brain = new Brain(*other.brain);
}

void Cat::makeSound() const
{
	std::cout << "Miau Miau" << std::endl;
}