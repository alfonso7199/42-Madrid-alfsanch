#include "Fixed.hpp"

const int Fixed::fractionalBits = 8;

Fixed::Fixed() : fixedPointNum(0) {
    std::cout << "Default constructor called\n";
}

Fixed::~Fixed() {
    	std::cout << "Destructor called\n";
}

Fixed &Fixed::operator=(const Fixed &other) {
    std::cout << "Copy assignment operator called\n";
	setRawBits(other.getRawBits());
	return (*this);
}

Fixed::Fixed(const Fixed &other) {
    std::cout << "Copy constructor called\n";
	*this = other;
}

int Fixed::getRawBits( void ) const {
    std::cout << "getRawBits member function called\n";
	return (fixedPointNum);
}

void Fixed::setRawBits( int const raw ){
    fixedPointNum = raw;
}

