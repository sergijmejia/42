#include "ScavTrap.hpp"

int main(void) {
    std::cout << "\n===== PHASE 1: CONSTRUCTION CHAIN =====" << std::endl;
    // We create a basic ClapTrap to compare
    ClapTrap basicBot("CLAP-99");
    
    // We create our new ScavTrap
    // Expected: ClapTrap constructor is called FIRST, then ScavTrap constructor
    ScavTrap advancedBot("SCAV-01");

    std::cout << "\n===== PHASE 2: TESTING CANONICAL FORM =====" << std::endl;
    // Test Copy Constructor
    ScavTrap cloneBot(advancedBot);
    // Test Assignment Operator
    ScavTrap assignBot("EMPTY");
    assignBot = advancedBot;

    std::cout << "\n===== PHASE 3: OVERRIDDEN ACTION (ATTACK) =====" << std::endl;
    // ClapTrap attack (costs 1 energy, does 0 damage usually)
    basicBot.attack("a training dummy");
    
    // ScavTrap attack (costs 1 energy, does 20 damage, different message)
    advancedBot.attack("a heavily armored dummy");

    std::cout << "\n===== PHASE 4: INHERITED ACTIONS =====" << std::endl;
    // ScavTrap should be able to take damage and heal using ClapTrap's functions perfectly
    // It starts with 100 HP. Let's hit it for 30.
    advancedBot.takeDamage(30);
    // Now it should heal (costs 1 energy, recovers HP)
    advancedBot.beRepaired(10);

    std::cout << "\n===== PHASE 5: SPECIAL ABILITY =====" << std::endl;
    // Only ScavTrap can do this. If you try basicBot.guardGate(), it would not compile!
    advancedBot.guardGate();

    std::cout << "\n===== PHASE 6: DESTRUCTION CHAIN =====" << std::endl;
    // Expected: When they die, ScavTrap destructor is called FIRST, then ClapTrap destructor
    return 0;
}