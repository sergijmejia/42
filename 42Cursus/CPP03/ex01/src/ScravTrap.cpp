#include "ScravTrap.hpp"

ScavTrap::ScavTrap(void) : ClapTrap(void) {
    _hitPoints = 100;
    _energyPoints = 50;
    _attackDamage = 20;
    std::cout << "Default ScravTrap constructor called" << std::endl;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name) {
    _hitPoints = 100;
    _energyPoints = 50;
    _attackDamage = 20;
    std::cout << "Constructor with name called" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& other) : ClapTrap(other) {
}

ClapTrap& ClapTrap::operator= (const ClapTrap& other) {
    if (this != &other) {
        this->_name = other.getName();
        this->_hitPoints = other.getHitPoints();
        this->_energyPoints = other.getEnergyPoints();
        this->_attackDamage = other.getAttackDamage();
    }
    return *this;
}

ClapTrap::~ClapTrap(void) {
    std::cout << "Destructor called" << std::endl;
}

std::string ClapTrap::getName(void) const {
    return _name;
}

int ClapTrap::getHitPoints(void) const {
    return _hitPoints;
}

int ClapTrap::getEnergyPoints(void) const {
    return _energyPoints;
}

int ClapTrap::getAttackDamage(void) const {
    return _attackDamage;
}

void ClapTrap::attack(const std::string& target) {
    if (_energyPoints == 0) {
        std::cout << "ClapTrap " << _name << " has 0 energy points. Can't do any action." << std::endl;
        return;
    }
    if (_hitPoints == 0) {
        std::cout << "ClapTrap " << _name << " has 0 hit points. Can't do any action." << std::endl;
        return;
    }
    _energyPoints--;
    std::cout << "ClapTrap " << _name << " attacks " << target << ", causing " << _attackDamage << " points of damage!" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount) {
    if (_hitPoints <= 0) {
        std::cout << "ClapTrap " << _name << " is already dead!" << std::endl;
        return;
    }
    if (amount >= (unsigned int)_hitPoints) {
        std::cout << "ClapTrap " << _name << " takes " << _hitPoints << " points of damage and dies! (0 hit points left)." << std::endl;
        _hitPoints = 0;
    } else {
        _hitPoints -= amount;
        std::cout << "ClapTrap " << _name << " takes " << amount << " points of damage. Now has " << _hitPoints << " hit points." << std::endl;
    }
    return;
}

void ClapTrap::beRepaired(unsigned int amount) {
    if (_energyPoints == 0) {
        std::cout << "ClapTrap " << _name << " has 0 energy points. Can't do any action." << std::endl;
        return;
    }
    if (_hitPoints == 0) {
        std::cout << "ClapTrap " << _name << " has 0 hit points. Can't do any action." << std::endl;
        return;
    }
    _energyPoints--;
    _hitPoints = _hitPoints + amount;
    std::cout << "ClapTrap " << _name << " get repaired. Now has " << _hitPoints << " hit points." << std::endl;
    return;
}
