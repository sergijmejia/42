#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongCat.hpp"

int main()
{
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();

    std::cout << j->getType() << " " << std::endl;
    std::cout << i->getType() << " " << std::endl;
    i->makeSound();
    j->makeSound();
    meta->makeSound();

    delete i;
    delete j;
    delete meta;

    /*
    std::cout << "\n--- TESTING WRONG ANIMALS ---" << std::endl;
    // Creating a WrongAnimal pointer pointing to a WrongCat object
    const WrongAnimal* wrong_cat = new WrongCat();

    // THE MOMENT OF TRUTH!
    wrong_cat->makeSound(); 

    delete wrong_cat;
    */

    return 0;
}