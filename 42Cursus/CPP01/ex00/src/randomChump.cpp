#include "Zombie.hpp"

void    randomChump(std::string name) {
    Zombie  zombieNew = Zombie();
    zombieNew.setName(name);
    zombieNew.announce();
    return;
}