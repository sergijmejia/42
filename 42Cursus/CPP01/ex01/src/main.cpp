#include "Zombie.hpp"

int main (void) {
    Zombie* horde;
    int     n = 20;

    std::cout << "First we will use the function zombieHorde" << std::endl;
    horde = zombieHorde(n, "Minion");
    std::cout << "The zombie horde of " << horde->getName() << " was created. Say hello guys" << std::endl << std::endl;
    for (int i = 0; i < n; i++) {
        horde[i].announce();
    }
    std::cout << std::endl << "Curious. I thought we would hear some \"banana\" there" << std::endl << std::endl;
    std::cout << "This entire horde will be here until we delete it." << std::endl;
    std::cout << "But it has to be deleted all at the same time, not one by one. I will do it now." << std::endl << std::endl;
    delete [] horde;

    std::cout << std::endl << "Now there are no \"alive\" zombies. The program can be finished without any risk of leaving any still reachable memory leaks" << std::endl;
    return (0);
}