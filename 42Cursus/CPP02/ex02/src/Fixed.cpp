#include "Fixed.hpp"

Fixed::Fixed() {
    std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed& other) {
    std::cout << "Copy constructor called" << std::endl;

    *this = other;
}

Fixed& Fixed::operator= (const Fixed& other) {
    std::cout << "Copy assignment operator called" << std::endl;

    if (this != &other) {
        this->_numberValue = other._numberValue;
    }
    return *this;
}

Fixed::~Fixed() {
    std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits(void) const {
    std::cout << "getRawBits member function called" << std::endl;

    return _numberValue;
}

void Fixed::setRawBits(int const raw) {
    std::cout << "setRawBits member function called" << std::endl;

    _numberValue = raw;
    return;
}

Fixed::Fixed(const int externalParameter) {
    std::cout << "Int constructor called" << std::endl;

    _numberValue = externalParameter << _fractionalBits;
}

Fixed::Fixed(const float externalParameter) {
    std::cout << "Float constructor called" << std::endl;

    _numberValue = roundf(externalParameter * (1 << _fractionalBits));
}

float Fixed::toFloat(void) const {
    return (float)_numberValue / (float)(1 << _fractionalBits);
}
        
int Fixed::toInt(void) const {
    int i = _numberValue >> _fractionalBits;
    return i;
}

std::ostream& operator<< (std::ostream& os, const Fixed& obj) {
        os << obj.toFloat();
        return os;
};

Fixed operator+ (const Fixed& other) const {
    Fixed result;
    result.setRawBits(this->_numberValue + other._numberValue);
    return result;
};

Fixed operator- (const Fixed& other) const {
    Fixed result;
    result.setRawBits(this->_numberValue - other._numberValue);
    return result;
};

Fixed operator* (const Fixed& other) const {
    Fixed result;
    result.setRawBits(((long)(this->_numberValue) - (long)(other._numberValue)) >> _fractionalBits);
    return result;
}
Fixed operator/ (const Fixed& other) const
/*Increment/Decrement*/
Fixed& operator++(void);
Fixed operator++(int);
Fixed& operator--(void);
Fixed operator--(int)
/*Overloaded Member Functions*/
static Fixed& min(Fixed& first, Fixed& second);
static const Fixed& min(const Fixed& first, const Fixed& second);
static Fixed& max(Fixed& first, Fixed& second);
static const Fixed& max(const Fixed& first, const Fixed& second;