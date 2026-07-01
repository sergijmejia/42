#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <string>
# include <cmath>

class Fixed {
    private:
        int                 _numberValue;
        static const int    _fractionalBits = 8;

    public:
        /*Default Constructor*/
        Fixed();

        /*Copy Constructor*/
        Fixed(const Fixed& other);

        /*Copy assignment operator*/
        Fixed& operator= (const Fixed& other);

        /*Destructor*/
        ~Fixed();

        /*Getters*/
        int getRawBits(void) const;

        /*Setters*/
        void    setRawBits(int const raw);

        /*Paramatrized Constructors*/
        Fixed(const int externalParameter);
        Fixed(const float externalParameter);

        /*Members Functions*/
        float toFloat(void) const;
        int toInt(void) const;

        /*Comparison Operators*/
        bool operator> (const Fixed& other) const;
        bool operator< (const Fixed& other) const;
        bool operator>= (const Fixed& other) const;
        bool operator<= (const Fixed& other) const;
        bool operator== (const Fixed& other) const;
        bool operator!= (const Fixed& other) const;

        /*Arithmetic Operators*/
        Fixed operator+ (const Fixed& other) const;
        Fixed operator- (const Fixed& other) const;
        Fixed operator* (const Fixed& other) const;
        Fixed operator/ (const Fixed& other) const;

        /*Increment/Decrement*/
        Fixed& operator++(void);
        Fixed operator++(int);
        Fixed& operator--(void);
        Fixed operator--(int);

        /*Overloaded Member Functions*/
        static Fixed& min(Fixed& first, Fixed& second);
        static const Fixed& min(const Fixed& first, const Fixed& second);
        static Fixed& max(Fixed& first, Fixed& second);
        static const Fixed& max(const Fixed& first, const Fixed& second);

};

std::ostream& operator<< (std::ostream& os, const Fixed& obj);

#endif