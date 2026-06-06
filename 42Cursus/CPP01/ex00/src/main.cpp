#include "Zombie.hpp"

int main (void) {
    Zombie* boss;

    std::cout << "First we will use the function newZombie" << std::endl;
    boss = newZombie("Nemesis");
    std::cout << "The zombie " << boss->getName() << " was created and is still... \"alive\"" << std::endl;
    boss->announce();
    std::cout << "(There it is)" << std::endl << std::endl;

    std::cout << "Now we will use the function randomChump" << std::endl;
    randomChump("Ephemeral");
    std::cout << "The zombie was created in the randomChump function and was destroyed when that function finished" << std::endl << std::endl;

    boss->announce();
    std::cout << "(Yes... it is still here...)" << std::endl; 
    std::cout << boss->getName() << " will be here until we delete it manually. I will do it now" << std::endl;
    delete boss;

    std::cout << std::endl << "Now there are no \"alive\" zombies. The program can be finished without any risk of leaving any still reachable memory leaks" << std::endl;
    return (0);
}