#include "Cat.hpp"

Cat::Cat(void) : A_Animal() {
    _type = "Cat";
    _brain = new Brain();
    std::cout << "Cat default constructor called" << std::endl; 
}

Cat::Cat(const Cat& other) : A_Animal(other) {
    if (other._brain != NULL) {
        _brain = new Brain(*other._brain);
    } else {
        _brain = NULL;
    }
    std::cout << "Cat copy constructor called" << std::endl;
}

Cat& Cat::operator= (const Cat& other) {
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

Cat::~Cat(void) {
    if (_brain != NULL) {
        delete _brain;
    }
    std::cout << "Cat destructor called" << std::endl;
}

void Cat::makeSound(void) const {
    std::cout << "Miau!" << std::endl;
    return;
}
