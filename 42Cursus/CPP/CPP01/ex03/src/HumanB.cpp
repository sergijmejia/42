#include "HumanB.hpp"

HumanB::HumanB(void) {
}

HumanB::HumanB(const std::string& newName) {
    _name = newName;
}

HumanB::~HumanB(void) {
}

void HumanB::setName(const std::string& newName) {
    _name = newName;
}

void HumanB::setWeapon(Weapon& newWeapon) {
    _weaponB = &(newWeapon);
}

Weapon* HumanB::getWeapon(void) const {
    return (_weaponB);
}

const std::string& HumanB::getName(void) const {
    return _name;
} 

void HumanB::attack(void) const{
    std::cout << _name <<" attacks with their " << (*_weaponB).getType() << std::endl;
}