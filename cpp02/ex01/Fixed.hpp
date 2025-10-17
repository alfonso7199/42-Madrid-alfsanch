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
};

std::ostream& operator<<(std::ostream &o, Fixed const &fixed);

#endif