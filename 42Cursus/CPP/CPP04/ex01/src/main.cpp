#include "Dog.hpp"
#include "Cat.hpp"

int main() {
    std::cout << "\n=====================================" << std::endl;
    std::cout << "1. ARRAY OF ANIMALS TEST" << std::endl;
    std::cout << "=====================================\n" << std::endl;
    
    const int numAnimals = 4;
    Animal* animals[numAnimals];

    // Filling half with Dogs and the other half with Cats
    for (int i = 0; i < numAnimals; i++) {
        std::cout << "Creating animal " << i << ":" << std::endl;
        if (i < numAnimals / 2) {
            animals[i] = new Dog();
        } else {
            animals[i] = new Cat();
        }
        std::cout << std::endl;
    }

    std::cout << "\n--- Destroying the array of animals ---" << std::endl;
    for (int i = 0; i < numAnimals; i++) {
        std::cout << "Destroying animal " << i << ":" << std::endl;
        delete animals[i];
        std::cout << std::endl;
    }

    std::cout << "\n=====================================" << std::endl;
    std::cout << "2. DEEP COPY TEST" << std::endl;
    std::cout << "=====================================\n" << std::endl;

    std::cout << "--- Creating original dog ---" << std::endl;
    Dog originalDog;
    
    std::cout << "\n--- Creating a temporary scope block ---" << std::endl;
    {
        std::cout << "Creating dog copy..." << std::endl;
        Dog copyDog = originalDog; // Calls the copy constructor
        
        std::cout << "Exiting temporary scope..." << std::endl;
    } // THE COPY DIES HERE! 
      // If it weren't a Deep Copy, it would destroy the original's brain.

    std::cout << "\nThe original dog survived the death of its copy." << std::endl;
    std::cout << "Finishing program...\n" << std::endl;

    return 0;
}