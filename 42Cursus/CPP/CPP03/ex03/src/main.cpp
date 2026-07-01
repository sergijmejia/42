#include "DiamondTrap.hpp"

int main(void) {
    std::cout << "\n===== PHASE 1: THE BIRTH OF THE MONSTER =====" << std::endl;
    // You should see the construction chain: ClapTrap -> ScavTrap -> FragTrap -> DiamondTrap
    std::cout << "--- Creating DiamondTrap with name 'DIAMOND' ---" << std::endl;
    DiamondTrap monster("DIAMOND");

    std::cout << "\n--- Creating DiamondTrap with default constructor ---" << std::endl;
    DiamondTrap defaultMonster;

    std::cout << "\n===== PHASE 2: TESTING STATS & ATTACK (THE HYBRID NATURE) =====" << std::endl;
    // Should use ScavTrap's attack (messages and logic) but with FragTrap's damage (30)
    monster.attack("a poor training dummy");

    // Let's force the use of inherited special skills from both parents
    std::cout << "\n--- Testing inherited special skills ---" << std::endl;
    monster.guardGate();      // From ScavTrap
    monster.highFivesGuys();  // From FragTrap

    std::cout << "\n===== PHASE 3: IDENTITY CRISIS (whoAmI) =====" << std::endl;
    // Should print its own name ("DIAMOND") and its grandfather's name ("DIAMOND_clap_name")
    std::cout << "--- Testing 'monster' identity ---" << std::endl;
    monster.whoAmI();

    std::cout << "\n--- Testing 'defaultMonster' identity ---" << std::endl;
    defaultMonster.whoAmI();

    std::cout << "\n===== PHASE 4: ORTHODOX CANONICAL FORM (MEMORY & COPY) =====" << std::endl;
    std::cout << "--- Testing Copy Constructor ---" << std::endl;
    // Create a clone using the copy constructor
    DiamondTrap clone(monster);
    std::cout << "Clone identity check:" << std::endl;
    clone.whoAmI();

    std::cout << "\n--- Testing Copy Assignment Operator ---" << std::endl;
    // Use the copy assignment operator
    defaultMonster = monster;
    std::cout << "Default monster (now assigned) identity check:" << std::endl;
    defaultMonster.whoAmI();

    std::cout << "\n===== PHASE 5: THE DESTRUCTION CHAIN =====" << std::endl;
    // Upon exiting main, you will see them destroyed in reverse order.
    // For DiamondTrap you will see: DiamondTrap -> FragTrap -> ScavTrap -> ClapTrap
    return 0;
}