#include "Animal.hpp"

Animal::Animal(void) {
    std::cout << "Animal default constructor called" << std::endl;
}

Animal::Animal(std::string newType) : _type(newType) {
    std::cout << "Animal constructor with type called" << std::endl;
}

Animal::Animal(const Animal& other) {
    _type = other._type;
    std::cout << "Animal copy constructor called" << std::endl;
}

Animal& Animal::operator= (const Animal& other) {
    if (this != &other) {
        this->_type = other._type;
    }
    return *this;
}

Animal::~Animal(void) {
    std::cout << "** Animal destructor called **" << std::endl;
}

void Animal::makeSound(void) const {
    std::cout << "** generic animal sounds **" << std::endl;
    return;
}

