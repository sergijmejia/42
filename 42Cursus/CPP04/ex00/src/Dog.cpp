#include "Dog.hpp"

Dog::Dog(void) : Animal() {
    std::cout << "Dog default constructor called" << std::endl;
}

Dog::Dog(const Dog& other) : Animal(other) {
    std::cout << "Dog copy constructor called" << std::endl;
}

Dog& Dog::operator= (const Dog& other) {
    if (this != &other) {
        Animal::operator=(other);
    }
    return *this;
}

Dog::~Dog(void) {
    std::cout << "Dog destructor called" << std::endl;
}

void Dog::makeSound(void) const {
    std::cout << "Guau!" << std::endl;
}

