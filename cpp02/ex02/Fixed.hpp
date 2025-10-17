#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <string>
#include <cmath>

class Fixed {
    private:
        int fixedPointNum;
        static const int fractionalBits;
    public:
        Fixed();
        Fixed(const Fixed &other);
        Fixed &operator=(const Fixed &other);
        ~Fixed();
        Fixed(const int n);
        Fixed(const float n);

        int     getRawBits( void ) const;
        void    setRawBits( int const raw );
        float   toFloat( void ) const;        
        int     toInt( void ) const;

        bool operator > (const Fixed &other) const;
		bool operator < (const Fixed &other) const;
		bool operator >= (const Fixed &other) const;
		bool operator <= (const Fixed &other) const;
		bool operator == (const Fixed &other) const;
		bool operator != (const Fixed &other) const;

		Fixed operator + (const Fixed &other) const;
		Fixed operator - (const Fixed &other) const;
		Fixed operator * (const Fixed &other) const;
		Fixed operator / (const Fixed &other) const;

		Fixed operator ++ (void);
		Fixed operator ++ (int);
		Fixed operator -- (void);
		Fixed operator -- (int);

        const static Fixed	&min(Fixed const &a, Fixed const &b);
		const static Fixed	&max(Fixed const &a, Fixed const &b);
};

std::ostream& operator<<(std::ostream &o, Fixed const &fixed);

#endif