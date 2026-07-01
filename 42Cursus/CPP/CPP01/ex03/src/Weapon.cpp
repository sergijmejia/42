#include "Weapon.hpp"

Weapon::Weapon(void) {
}

Weapon::Weapon(const std::string& newValue) : type(newValue) {
}

Weapon::~Weapon(void) {
}

void Weapon::setType(const std::string& newValue) {
    type = newValue;
}

const std::string& Weapon::getType(void) const {
    return type;
}
