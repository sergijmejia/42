#include "HumanA.hpp"

HumanA::HumanA(const std::string& newName, Weapon& newWeapon) : _weaponA(newWeapon) {
    _name = newName;
}

HumanA::~HumanA(void) {
}

void HumanA::setName(const std::string& newName) {
    _name = newName;
}

const Weapon& HumanA::getWeapon(void) const {
    return _weaponA;
}

const std::string& HumanA::getName(void) const {
    return _name;
} 

void HumanA::attack(void) const{
    std::cout << _name <<" attacks with their " << _weaponA.getType() << std::endl;
}