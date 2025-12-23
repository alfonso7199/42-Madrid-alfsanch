#include "AMateria.hpp"

AMateria::AMateria()
{
	std::cout << "AMateria default constructor called" << std::endl;
}

AMateria::~AMateria()
{
	std::cout << "AMateria object destroyed" << std::endl;
}

AMateria &AMateria::operator=(const AMateria &other)
{
    std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other)
	{
		this->type = other.type;
	}
	return (*this);
}

AMateria::AMateria(const AMateria &other)
{
    std::cout << "Copy constructor called" << std::endl;
	this->type = other.type;
}

std::string AMateria::getType() const
{
	return this->type;
}