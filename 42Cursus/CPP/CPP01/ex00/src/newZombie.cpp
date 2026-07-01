#include "Zombie.hpp"

Zombie* newZombie(std::string name ) {
    Zombie* zombieNew = new Zombie();
    zombieNew->setName(name);
    return (zombieNew);
}