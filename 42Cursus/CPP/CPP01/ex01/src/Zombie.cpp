#include "Zombie.hpp"

Zombie::Zombie( void ) {
}

Zombie::~Zombie( void ) {
    std::cout << "(zombie " << _name << " was destroyed)" << std::endl;
}

void    Zombie::setName(std::string zombieName) {
    _name = zombieName;
}

void    Zombie::announce() {
    std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

std::string Zombie::getName(void) {
    return _name;
}

