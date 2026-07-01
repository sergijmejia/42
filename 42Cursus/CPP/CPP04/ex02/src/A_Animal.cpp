#include "A_Animal.hpp"

A_Animal::A_Animal(void) {
    _type = "A_Animal";
    std::cout << "A_Animal default constructor called" << std::endl;
}

A_Animal::A_Animal(std::string newType) : _type(newType) {
    std::cout << "A_Animal constructor with type called" << std::endl;
}

A_Animal::A_Animal(const A_Animal& other) {
    _type = other._type;
    std::cout << "A_Animal copy constructor called" << std::endl;
}

A_Animal& A_Animal::operator= (const A_Animal& other) {
    if (this != &other) {
        this->_type = other._type;
    }
    return *this;
}

A_Animal::~A_Animal(void) {
    std::cout << "** A_Animal destructor called **" << std::endl;
}

std::string A_Animal::getType(void) const {
    return _type;
}
