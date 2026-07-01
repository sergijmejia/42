#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main(void) {
    std::cout << "\n===== PHASE 1: CREATING THE CHAMPIONS =====" << std::endl;
    // Expected: 1 message (ClapTrap)
    ClapTrap basicBot("CLAPPY");
    
    // Expected: 2 messages (ClapTrap -> ScavTrap)
    ScavTrap guardBot("SCAVY");
    
    // Expected: 2 messages (ClapTrap -> FragTrap)
    FragTrap smashBot("FRAGGY");

    std::cout << "\n===== PHASE 2: TESTING ATTACKS (THE DIFFERENCES) =====" << std::endl;
    // Uses base attack (0 damage)
    basicBot.attack("a training dummy");
    
    // Uses overridden attack (20 damage, ScavTrap message)
    guardBot.attack("an intruder");
    
    // Uses inherited attack (30 damage, ClapTrap message as intended)
    smashBot.attack("a concrete wall");

    std::cout << "\n===== PHASE 3: DAMAGE AND REPAIR (FRAGTRAP STATS) =====" << std::endl;
    // FragTrap starts with 100 HP. Takes 50 damage.
    smashBot.takeDamage(50);
    
    // FragTrap heals 25 HP. Costs 1 of his 100 EP.
    smashBot.beRepaired(25);

    std::cout << "\n===== PHASE 4: SPECIAL ABILITIES =====" << std::endl;
    // ScavTrap unique skill
    guardBot.guardGate();
    
    // FragTrap unique skill
    smashBot.highFivesGuys();

    std::cout << "\n===== PHASE 5: THE DESTRUCTION CHAIN =====" << std::endl;
    // Expected: They will die in reverse order of creation
    // 1st: smashBot (FragTrap -> ClapTrap)
    // 2nd: guardBot (ScavTrap -> ClapTrap)
    // 3rd: basicBot (ClapTrap)
    
    return 0;
}