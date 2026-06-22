#include "WrongCat.hpp"

WrongCat::WrongCat(void) : WrongAnimal() {
    std::cout << "WrongCat default constructor called" << std::endl;
}

WrongCat::WrongCat(const WrongCat& other) : WrongAnimal(other) {
    std::cout << "WrongCat copy constructor called" << std::endl;
}

WrongCat& WrongCat::operator= (const WrongCat& other) {
    if (this != &other) {
        WrongAnimal::operator=(other);
    }
    return *this;
}

WrongCat::~WrongCat(void) {
    std::cout << "WrongCat destructor called" << std::endl;
}

void WrongCat::makeSound(void) const {
    std::cout << "Miau!" << std::endl;
    return;
}
