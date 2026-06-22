#include "Dog.hpp"

Dog::Dog(void) : A_Animal() {
    _type = "Dog";
    _brain = new Brain();
    std::cout << "Dog default constructor called" << std::endl; 
}

Dog::Dog(const Dog& other) : A_Animal(other) {
    if (other._brain != NULL) {
        _brain = new Brain(*other._brain);
    } else {
        _brain = NULL;
    }
    std::cout << "Dog copy constructor called" << std::endl;
}

Dog& Dog::operator= (const Dog& other) {
    if (this != &other) {
        A_Animal::operator=(other);
        if (_brain != NULL) {
            delete _brain;
            _brain = NULL;
        }
        if (other._brain != NULL) {
            _brain = new Brain(*other._brain);
        }
    }
    return *this;
}

Dog::~Dog(void) {
    if (_brain != NULL) {
        delete _brain;
    }
    std::cout << "Dog destructor called" << std::endl;
}

void Dog::makeSound(void) const {
    std::cout << "Guau!" << std::endl;
    return;
}

