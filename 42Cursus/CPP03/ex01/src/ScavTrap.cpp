#include "ScavTrap.hpp"

ScavTrap::ScavTrap(void) : ClapTrap() {
    _hitPoints = 100;
    _energyPoints = 50;
    _attackDamage = 20;
    std::cout << "Default ScravTrap constructor called" << std::endl;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name) {
    _hitPoints = 100;
    _energyPoints = 50;
    _attackDamage = 20;
    std::cout << "Constructor ScravTrap with name called" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& other) : ClapTrap(other) {
    std::cout << "Copy constructor ScavTrap called" << std::endl;
}

ScavTrap& ScavTrap::operator= (const ScavTrap& other) {
    if (this != &other) {
        ClapTrap::operator=(other);
    }
    return *this;
}

ScavTrap::~ScavTrap(void) {
    std::cout << "Destructor ScavTrap called" << std::endl;
}

void ScavTrap::attack(const std::string& target) {
    if (_energyPoints == 0) {
        std::cout << "ScavTrap " << _name << " has 0 energy points. Can't do any action." << std::endl;
        return;
    }
    if (_hitPoints == 0) {
        std::cout << "ScavTrap " << _name << " has 0 hit points. Can't do any action." << std::endl;
        return;
    }
    _energyPoints--;
    std::cout << "ScavTrap " << _name << " attacks " << target << ", causing " << _attackDamage << " points of damage!" << std::endl;
} 

void ScavTrap::guardGate(void) {
    std::cout << "ScavTrap " << _name << "  is now in Gate keeper mode " << std::endl;
}
