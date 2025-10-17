#include "Fixed.hpp"

const int Fixed::fractionalBits = 8;

Fixed::Fixed() : fixedPointNum(0) {
    std::cout << "Default constructor called\n";
}

Fixed::Fixed(const int n) : fixedPointNum(0) {
    std::cout << "Int constructor called\n";
    fixedPointNum = n << fractionalBits;
}

Fixed::Fixed(const float n) : fixedPointNum(0) {
    std::cout << "Float constructor called\n";
    fixedPointNum = (int)roundf(n * (1 << fractionalBits));
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
	return (fixedPointNum);
}

void Fixed::setRawBits( int const raw ){
    fixedPointNum = raw;
}

float Fixed::toFloat(void) const {
    return (float)fixedPointNum / (float)(1 << fractionalBits);
}

int Fixed::toInt(void) const {
    return (int)(fixedPointNum >> fractionalBits);
}

std::ostream& operator<<(std::ostream &o, Fixed const &fixed) {
	o << fixed.toFloat();
	return o;
}