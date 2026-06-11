#include "Fixed.hpp"

Fixed::Fixed() {
    std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed& other) {
    std::cout << "Copy constructor called" << std::endl;

    _numberValue = other.getRawBits();
}

Fixed& Fixed::operator= (const Fixed& other) {
    std::cout << "Copy assignment operator called" << std::endl;

    if (this != &other) {
        this->_numberValue = other.getRawBits();
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