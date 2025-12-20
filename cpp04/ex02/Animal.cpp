#include "Animal.hpp"

Animal::Animal() : type("animal")
{
	std::cout << "Animal default constructor called" << std::endl;
}

Animal::Animal(std::string type) : type(type)
{
	std::cout << "Animal " << type << " created" << std::endl;
}

Animal::~Animal()
{
	std::cout << "Animal object " << type << " destroyed" << std::endl;
}

Animal &Animal::operator=(const Animal &other)
{
    std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other)
	{
		this->type = other.type;
	}
	return (*this);
}

Animal::Animal(const Animal &other)
{
    std::cout << "Copy constructor called" << std::endl;
	this->type = other.type;
}

std::string Animal::getType() const
{
	return this->type;
}