#include "Fixed.hpp"

const int Fixed::fractionalBits = 8;

Fixed::Fixed() : fixedPointNum(0) {
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


bool	Fixed::operator>(Fixed const &other) const {
	return getRawBits() > other.getRawBits();
}

bool	Fixed::operator<(Fixed const &other) const {
	return getRawBits() < other.getRawBits();
}

bool	Fixed::operator>=(Fixed const &other) const {
	return getRawBits() >= other.getRawBits();
}

bool	Fixed::operator<=(Fixed const &other) const {
	return getRawBits() <= other.getRawBits();
}

bool	Fixed::operator==(Fixed const &other) const {
	return getRawBits() == other.getRawBits();
}

bool	Fixed::operator!=(Fixed const &other) const {
	return getRawBits() != other.getRawBits();
}

Fixed	Fixed::operator+(Fixed const &other) const {
	Fixed	ret;
	ret.setRawBits(getRawBits() + other.getRawBits());
	return ret;
}

Fixed	Fixed::operator-(Fixed const &other) const {
	Fixed	ret;
	ret.setRawBits(getRawBits() - other.getRawBits());
	return ret;
}

Fixed	Fixed::operator*(Fixed const &other) const {
	Fixed	ret;
	ret.setRawBits(getRawBits() * other.getRawBits() >> fractionalBits);
	return ret;
}

Fixed	Fixed::operator/(Fixed const &other) const {
	Fixed	ret;
	ret.setRawBits(getRawBits() / other.getRawBits() << fractionalBits);
	return ret;
}

Fixed&	Fixed::operator++() {
	fixedPointNum++;
	return *this;
}

Fixed	Fixed::operator++(int) {
	Fixed	tmp(*this);
	operator++();
	return tmp;
}

Fixed&	Fixed::operator--() {
	fixedPointNum--;
	return *this;
}

Fixed	Fixed::operator--(int) {
	Fixed	tmp(*this);
	operator--();
	return tmp;
}

Fixed const &Fixed::min(Fixed const &a, Fixed const &b) {
	return a < b ? a : b;
}

Fixed &Fixed::min(Fixed &a, Fixed &b) {
	return a < b ? a : b;
}

Fixed const &Fixed::max(Fixed const &a, Fixed const &b) {
	return a > b ? a : b;
}

Fixed &Fixed::max(Fixed &a, Fixed &b) {
	return a > b ? a : b;
}