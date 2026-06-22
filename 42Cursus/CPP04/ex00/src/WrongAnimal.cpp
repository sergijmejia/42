#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal(void) {
    std::cout << "WrongAnimal default constructor called" << std::endl;
}

WrongAnimal::WrongAnimal(std::string newType) : _type(newType) {
    std::cout << "WrongAnimal constructor with type called" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal& other) {
    _type = other._type;
    std::cout << "WrongAnimal copy constructor called" << std::endl;
}

WrongAnimal& WrongAnimal::operator= (const WrongAnimal& other) {
    if (this != &other) {
        this->_type = other._type;
    }
    return *this;
}

WrongAnimal::~WrongAnimal(void) {
    std::cout << "** WrongAnimal destructor called **" << std::endl;
}

void WrongAnimal::makeSound(void) const {
    std::cout << "** generic WrongAnimal sounds **" << std::endl;
    return;
}

