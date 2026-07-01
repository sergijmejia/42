#include "ClapTrap.hpp"

int main(void) {
    std::cout << "\n--- STARTING THE COMBAT ARENA ---" << std::endl;

    // 1. Testing Constructors (Canonical Form)
    std::cout << "\n[PHASE 1: FIGHTER CREATION]" << std::endl;
    ClapTrap robot1("R2D2");
    ClapTrap robot2("C3PO");
    
    // Testing copy constructor and assignment operator
    ClapTrap cloneOfR2D2(robot1); 
    ClapTrap robot3;
    robot3 = robot2;

    // 2. Testing basic combat
    std::cout << "\n[PHASE 2: BASIC COMBAT]" << std::endl;
    // R2D2 attacks C3PO (R2D2 spends 1 energy point)
    robot1.attack("C3PO"); 
    // Since the default damage of a ClapTrap is 0, C3PO takes 0 damage, 
    // but we will force manual damage to test the takeDamage function.
    robot2.takeDamage(5); 

    // 3. Testing repair
    std::cout << "\n[PHASE 3: REPAIR]" << std::endl;
    // C3PO heals himself
    robot2.beRepaired(3);

    // 4. Pushing energy to the limit (Depletion)
    std::cout << "\n[PHASE 4: ENERGY DEPLETION TEST]" << std::endl;
    // R2D2 attacks 10 times in a row to deplete his initial battery
    for (int i = 0; i < 10; i++) {
        robot1.attack("a target dummy");
    }

    // 5. Testing lethal damage and death
    std::cout << "\n[PHASE 5: LETHAL DAMAGE AND DEATH]" << std::endl;
    // A giant missile hits C3PO
    robot2.takeDamage(50);
    
    // We try to make a dead robot do things (Protections should trigger)
    robot2.attack("R2D2");
    robot2.beRepaired(10);
    robot2.takeDamage(10); // Post-mortem damage

    std::cout << "\n--- END OF SIMULATION ---" << std::endl;

    return 0; // Destructors will be called automatically here
}