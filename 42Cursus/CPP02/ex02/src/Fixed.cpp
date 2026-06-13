#include "Fixed.hpp"

Fixed::Fixed() {
    this->_numberValue = 0;
}

Fixed::Fixed(const Fixed& other) {
    *this = other;
}

Fixed& Fixed::operator= (const Fixed& other) {
    if (this != &other) {
        this->_numberValue = other._numberValue;
    }
    return *this;
}

Fixed::~Fixed() {
}

int Fixed::getRawBits(void) const {
    return _numberValue;
}

void Fixed::setRawBits(int const raw) {
    _numberValue = raw;
    return;
}

Fixed::Fixed(const int externalParameter) {
    _numberValue = externalParameter << _fractionalBits;
}

Fixed::Fixed(const float externalParameter) {
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

Fixed Fixed::operator+ (const Fixed& other) const {
    Fixed result;
    result.setRawBits(this->_numberValue + other._numberValue);
    return result;
};

Fixed Fixed::operator- (const Fixed& other) const {
    Fixed result;
    result.setRawBits(this->_numberValue - other._numberValue);
    return result;
};

Fixed Fixed::operator* (const Fixed& other) const {
    Fixed   result;
    long    temp;
    temp = (long)(this->_numberValue) * (long)(other._numberValue);
    result.setRawBits((int)(temp >> _fractionalBits));
    return result;
};


Fixed Fixed::operator/ (const Fixed& other) const {
    Fixed   result;;
    long    temp;
    temp = (long)(this->_numberValue) << _fractionalBits;
    result.setRawBits((int)(temp / other._numberValue));
    return result;
};

Fixed& Fixed::operator++(void) {
    this->_numberValue++;
    return *this;
};

Fixed Fixed::operator++(int) {
    Fixed b(*this);
    this->_numberValue++;
    return b;
};

Fixed& Fixed::operator--(void) {
    this->_numberValue--;
    return *this;
};

Fixed Fixed::operator--(int) {
    Fixed b(*this);
    this->_numberValue--;
    return b;
};

Fixed& Fixed::min(Fixed& first, Fixed& second) {
    if (first._numberValue > second._numberValue)
        return second;
    return first;
};

const Fixed& Fixed::min(const Fixed& first, const Fixed& second) {
    if (first._numberValue > second._numberValue)
        return second;
    return first;
};

Fixed& Fixed::max(Fixed& first, Fixed& second) {
    if (first._numberValue < second._numberValue)
        return second;
    return first;
};

const Fixed& Fixed::max(const Fixed& first, const Fixed& second) {
    if (first._numberValue < second._numberValue)
        return second;
    return first;
};