#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal() : type("Wronganimal")
{
	std::cout << "WrongAnimal default constructor called" << std::endl;
}

WrongAnimal::WrongAnimal(std::string type) : type(type)
{
	std::cout << "WrongAnimal " << type << " created" << std::endl;
}

WrongAnimal::~WrongAnimal()
{
	std::cout << "WrongAnimal object " << type << " destroyed" << std::endl;
}

WrongAnimal &WrongAnimal::operator=(const WrongAnimal &other)
{
    std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other)
	{
		this->type = other.type;
	}
	return (*this);
}

WrongAnimal::WrongAnimal(const WrongAnimal &other)
{
    std::cout << "Copy constructor called" << std::endl;
	this->type = other.type;
}

void WrongAnimal::makeSound() const
{
	std::cout << "WrongAnimal make sound" << std::endl;
}

std::string WrongAnimal::getType() const
{
	return this->type;
}